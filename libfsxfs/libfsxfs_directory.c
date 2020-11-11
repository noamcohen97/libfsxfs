/*
 * Directory functions
 *
 * Copyright (C) 2020, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libfsxfs_block_directory.h"
#include "libfsxfs_definitions.h"
#include "libfsxfs_directory.h"
#include "libfsxfs_directory_entry.h"
#include "libfsxfs_directory_table.h"
#include "libfsxfs_inode.h"
#include "libfsxfs_io_handle.h"
#include "libfsxfs_libbfio.h"
#include "libfsxfs_libcdata.h"
#include "libfsxfs_libcerror.h"
#include "libfsxfs_libuna.h"

/* Creates a directory
 * Make sure the value directory is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsxfs_directory_initialize(
     libfsxfs_directory_t **directory,
     libcerror_error_t **error )
{
	static char *function = "libfsxfs_directory_initialize";

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
		 function );

		return( -1 );
	}
	if( *directory != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid directory value already set.",
		 function );

		return( -1 );
	}
	*directory = memory_allocate_structure(
	              libfsxfs_directory_t );

	if( *directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create directory.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *directory,
	     0,
	     sizeof( libfsxfs_directory_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear directory.",
		 function );

		memory_free(
		 *directory );

		*directory = NULL;

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( ( *directory )->entries_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create entries array.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *directory != NULL )
	{
		memory_free(
		 *directory );

		*directory = NULL;
	}
	return( -1 );
}

/* Frees a directory
 * Returns 1 if successful or -1 on error
 */
int libfsxfs_directory_free(
     libfsxfs_directory_t **directory,
     libcerror_error_t **error )
{
	static char *function = "libfsxfs_directory_free";
	int result            = 1;

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
		 function );

		return( -1 );
	}
	if( *directory != NULL )
	{
		if( libcdata_array_free(
		     &( ( *directory )->entries_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfsxfs_directory_entry_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free entries array.",
			 function );

			result = -1;
		}
		memory_free(
		 *directory );

		*directory = NULL;
	}
	return( result );
}

/* Reads the directory entries
 * Returns 1 if successful or -1 on error
 */
int libfsxfs_directory_read_file_io_handle(
     libfsxfs_directory_t *directory,
     libfsxfs_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfsxfs_inode_t *inode,
     libcerror_error_t **error )
{
	libfsxfs_block_directory_t *block_directory = NULL;
	libfsxfs_directory_table_t *directory_table = NULL;
	static char *function                       = "libfsxfs_directory_read_file_io_handle";
	off64_t file_offset                         = 0;

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
		 function );

		return( -1 );
	}
	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( inode == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid inode.",
		 function );

		return( -1 );
	}
	if( ( inode->file_mode & 0xf000 ) == LIBFSXFS_FILE_TYPE_DIRECTORY )
	{
		if( ( inode->fork_type != LIBFSXFS_FORK_TYPE_INLINE_DATA )
		 && ( inode->fork_type != LIBFSXFS_FORK_TYPE_EXTENTS ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported directory data fork type.",
			 function );

			goto on_error;
		}
		if( inode->fork_type == LIBFSXFS_FORK_TYPE_INLINE_DATA )
		{
			if( libfsxfs_directory_table_initialize(
			     &directory_table,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to initialize directory table.",
				 function );

				goto on_error;
			}
			if( libfsxfs_directory_table_read_data(
			     directory_table,
			     io_handle,
			     inode->inline_data,
			     (size_t) inode->size,
			     directory->entries_array,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read directory table.",
				 function );

				goto on_error;
			}
			if( libfsxfs_directory_table_free(
			     &directory_table,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free directory table.",
				 function );

				goto on_error;
			}
		}
		else if( inode->fork_type == LIBFSXFS_FORK_TYPE_EXTENTS )
		{
			if( libfsxfs_block_directory_initialize(
			     &block_directory,
			     io_handle->block_size,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to initialize block directory.",
				 function );

				goto on_error;
			}
/* TODO deterimine file offset from extents */
			file_offset = 861 * 4096;

			if( libfsxfs_block_directory_read_file_io_handle(
			     block_directory,
			     io_handle,
			     file_io_handle,
			     file_offset,
			     directory->entries_array,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read block directory.",
				 function );

				goto on_error;
			}
			if( libfsxfs_block_directory_free(
			     &block_directory,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free block directory.",
				 function );

				goto on_error;
			}
		}
	}
	return( 1 );

on_error:
	if( block_directory != NULL )
	{
		libfsxfs_block_directory_free(
		 &block_directory,
		 NULL );
	}
	if( directory_table != NULL )
	{
		libfsxfs_directory_table_free(
		 &directory_table,
		 NULL );
	}
	libcdata_array_empty(
	 directory->entries_array,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libfsxfs_directory_entry_free,
	 NULL );

	return( -1 );
}

/* Retrieves the number of entries
 * Returns 1 if successful or -1 on error
 */
int libfsxfs_directory_get_number_of_entries(
     libfsxfs_directory_t *directory,
     int *number_of_entries,
     libcerror_error_t **error )
{
	static char *function = "libfsxfs_directory_get_number_of_entries";

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     directory->entries_array,
	     number_of_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific entry
 * Returns 1 if successful or -1 on error
 */
int libfsxfs_directory_get_entry_by_index(
     libfsxfs_directory_t *directory,
     int entry_index,
     libfsxfs_directory_entry_t **directory_entry,
     libcerror_error_t **error )
{
	static char *function = "libfsxfs_directory_get_entry_by_index";

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     directory->entries_array,
	     entry_index,
	     (intptr_t **) directory_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry: %d.",
		 function,
		 entry_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the directory entry for an UTF-8 encoded name
 * Returns 1 if successful, 0 if not found or -1 on error
 */
int libfsxfs_directory_get_entry_by_utf8_name(
     libfsxfs_directory_t *directory,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libfsxfs_directory_entry_t **directory_entry,
     libcerror_error_t **error )
{
	libfsxfs_directory_entry_t *safe_directory_entry = NULL;
	static char *function                            = "libfsxfs_directory_get_entry_by_utf8_name";
	int entry_index                                  = 0;
	int number_of_entries                            = 0;
	int result                                       = 0;

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     directory->entries_array,
	     &number_of_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries.",
		 function );

		return( -1 );
	}
	for( entry_index = 0;
	     entry_index < number_of_entries;
	     entry_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     directory->entries_array,
		     entry_index,
		     (intptr_t **) &safe_directory_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve entry: %d.",
			 function,
			 entry_index );

			return( -1 );
		}
		result = libfsxfs_directory_entry_compare_with_utf8_string(
		          safe_directory_entry,
		          utf8_string,
		          utf8_string_length,
		          error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GENERIC,
			 "%s: unable to compare UTF-8 string with directory entry: %d.",
			 function,
			 entry_index );

			return( -1 );
		}
		else if( result == LIBUNA_COMPARE_EQUAL )
		{
			*directory_entry = safe_directory_entry;

			return( 1 );
		}
	}
	*directory_entry = NULL;

	return( 0 );
}

/* Retrieves the directory entry for an UTF-16 encoded name
 * Returns 1 if successful, 0 if not found or -1 on error
 */
int libfsxfs_directory_get_entry_by_utf16_name(
     libfsxfs_directory_t *directory,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libfsxfs_directory_entry_t **directory_entry,
     libcerror_error_t **error )
{
	libfsxfs_directory_entry_t *safe_directory_entry = NULL;
	static char *function                            = "libfsxfs_directory_get_entry_by_utf16_name";
	int entry_index                                  = 0;
	int number_of_entries                            = 0;
	int result                                       = 0;

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     directory->entries_array,
	     &number_of_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries.",
		 function );

		return( -1 );
	}
	for( entry_index = 0;
	     entry_index < number_of_entries;
	     entry_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     directory->entries_array,
		     entry_index,
		     (intptr_t **) &safe_directory_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve entry: %d.",
			 function,
			 entry_index );

			return( -1 );
		}
		result = libfsxfs_directory_entry_compare_with_utf16_string(
		          safe_directory_entry,
		          utf16_string,
		          utf16_string_length,
		          error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GENERIC,
			 "%s: unable to compare UTF-16 string with directory entry: %d.",
			 function,
			 entry_index );

			return( -1 );
		}
		else if( result == LIBUNA_COMPARE_EQUAL )
		{
			*directory_entry = safe_directory_entry;

			return( 1 );
		}
	}
	*directory_entry = NULL;

	return( 0 );
}


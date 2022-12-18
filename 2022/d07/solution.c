#include "../common/headers.h"
#include "input/data.h"

typedef struct directory {
  char *name;
  struct directory *parent;
  vec_t *children;
  size_t size;
  size_t total_size;
} directory_t;

typedef struct fs {
  directory_t *root;
  directory_t *cwd;
} fs_t;

void *create_directory(char *name, directory_t *parent) {
  directory_t *directory = malloc(sizeof(directory_t));
  directory->name = name;
  directory->parent = parent;
  directory->size = 0;
  directory->children = malloc(sizeof(vec_t));
  init_vec(directory->children);
  return directory;
}

void free_directory(directory_t *directory) {
  if (directory == NULL) {
    return;
  }
  iter_t iter = iter_begin_vec(directory->children, false);
  for (; iter.value != NULL; iter_next_vec(&iter)) {
    free_directory((directory_t *)iter.value);
  }
  free_vec(directory->children);
  free(directory->children);
  free(directory);
}

int find_dir_by_name(const void *data, const void *cmp) {
  const directory_t *dir = data;
  const char *name = cmp;
  return strcmp(dir->name, name) == 0;
}

void parse_directories(char *token, int index, void *data) {
  fs_t *fs = data;
  if (token[0] == '$') {
    char *dir_name = NULL;
    sscanf(token, "$ cd %ms", &dir_name);
    if (dir_name != NULL) {
      if (strcmp(dir_name, "/") == 0) {
        directory_t *d = create_directory(dir_name, NULL);
        fs->root = d;
        fs->cwd = d;
      } else if (strcmp(dir_name, "..") == 0) {
        fs->cwd = fs->cwd->parent;
      } else {
        fs->cwd = find_vec(fs->cwd->children, find_dir_by_name, dir_name);
      }
    }
  } else {
    if (strstr(token, "dir") != NULL) {
      char *dir_name = NULL;
      sscanf(token, "dir %ms", &dir_name);
      directory_t *d = create_directory(dir_name, fs->cwd);
      push_vec(fs->cwd->children, d);
    } else {
      size_t size;
      char *file;
      sscanf(token, "%lu %ms", &size, &file);
      fs->cwd->size += size;
    }
  }
}

size_t flat_folder_size(directory_t *directory) {
  if (directory == NULL) {
    return 0;
  }
  size_t total_size = directory->size;
  iter_t iter = iter_begin_vec(directory->children, false);
  for (; iter.value != NULL; iter_next_vec(&iter)) {
    total_size += flat_folder_size((directory_t *)iter.value);
  }
  directory->total_size = total_size;
  return total_size;
}

size_t recursive_filter_size(directory_t *directory, size_t filter_size) {
  if (directory == NULL) {
    return 0;
  }
  size_t total_size = 0;
  if (directory->total_size <= filter_size) {
    total_size += directory->total_size;
  }
  iter_t iter = iter_begin_vec(directory->children, false);
  for (; iter.value != NULL; iter_next_vec(&iter)) {
    total_size += recursive_filter_size((directory_t *)iter.value, filter_size);
  }
  return total_size;
}

void recursive_filter_smallest_directory(directory_t *directory,
                                         size_t filter_size,
                                         size_t *current_smallest) {
  if (directory == NULL || directory->total_size < filter_size) {
    return;
  }
  if (directory->total_size < *current_smallest) {
    *current_smallest = directory->total_size;
  }
  iter_t iter = iter_begin_vec(directory->children, false);
  for (; iter.value != NULL; iter_next_vec(&iter)) {
    recursive_filter_smallest_directory((directory_t *)iter.value, filter_size,
                                        current_smallest);
  }
}

int part1(char *input) {
  fs_t fs = {};
  map_delim(input, "\n", parse_directories, &fs);
  flat_folder_size(fs.root);
  size_t total_size = recursive_filter_size(fs.root, 100000);
  free_directory(fs.root);
  return total_size;
}

int part2(char *input) {
  fs_t fs = {};
  map_delim(input, "\n", parse_directories, &fs);
  flat_folder_size(fs.root);

  size_t total_disk_space = 70000000;
  size_t needed_disk_space = 30000000;
  size_t to_free_disk_space =
      needed_disk_space - (total_disk_space - fs.root->total_size);

  size_t current_smallest = SIZE_MAX;
  recursive_filter_smallest_directory(fs.root, to_free_disk_space,
                                      &current_smallest);
  free_directory(fs.root);
  return current_smallest;
}

AOC_MAIN(d07, 1315285, 9847279)
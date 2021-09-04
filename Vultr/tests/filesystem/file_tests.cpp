#include <gtest/gtest.h>
#define private public
#define protected public

#include <stdio.h>
#include <filesystem/file.h>

static const char *file_path = "test_file.txt";
static const char *file_extension = ".txt";
static const char *file_data = "string";

using namespace Vultr;
class Filesystem : public testing::Test
{
  protected:
    // Per-test-suite set-up.
    // Called before the first test in this test suite.
    // Can be omitted if not needed.
    static void SetUpTestSuite()
    {
        FILE *f = fopen(file_path, "w+");
        fputs(file_data, f);
        fclose(f);
    }

    // Per-test-suite tear-down.
    // Called after the last test in this test suite.
    // Can be omitted if not needed.
    static void TearDownTestSuite()
    {
        remove(file_path);
    }
};

TEST_F(Filesystem, FBasename)
{
    GenericFile file = GenericFile(file_path);
    EXPECT_TRUE(strequal(fbasename(&file), file_path));
}

TEST_F(Filesystem, FExtension)
{
    GenericFile file = GenericFile(file_path);
    EXPECT_TRUE(strequal(fextension(&file), file_extension));

    file = GenericFile("no_extension");
    EXPECT_EQ(fextension(&file), nullptr);
}

TEST_F(Filesystem, FRename)
{
    GenericFile file = GenericFile(file_path);
    file_path = "new_test_file.text";
    file_extension = ".text";
    frename(&file, file_path);

    EXPECT_TRUE(strequal(fextension(&file), file_extension));
    EXPECT_TRUE(strequal(fbasename(&file), file_path));

    FILE *f = fopen(file_path, "r");
#define READ_BUFFER_SIZE 32768
    char buffer[READ_BUFFER_SIZE];

    char *res_str = str("");

    while (!feof(f))
    {
        size_t bytes = fread(buffer, 1, sizeof(buffer), f);

        if (bytes)
        {
            res_str = strappend(res_str, buffer);
        }
    }
    EXPECT_TRUE(strequal(res_str, file_data));

    fclose(f);
}

TEST_F(Filesystem, FCopy)
{
    const char *copy_file_path = "copy_file.txt";
    GenericFile file = GenericFile(file_path);

    bool res = fcopy(&file, copy_file_path);
    ASSERT_TRUE(res);

    ASSERT_TRUE(strequal(file.path, copy_file_path));

    FILE *f = fopen(copy_file_path, "r");
#define READ_BUFFER_SIZE 32768
    char buffer[READ_BUFFER_SIZE];

    char *res_str = str("");

    while (!feof(f))
    {
        size_t bytes = fread(buffer, 1, sizeof(buffer), f);

        if (bytes)
        {
            res_str = strappend(res_str, buffer);
        }
    }
    EXPECT_TRUE(strequal(res_str, file_data));

    fclose(f);
}

TEST_F(Filesystem, FRemove_FExists)
{
    const char *copy_file_path = "copy_file.txt";
    GenericFile file = GenericFile(copy_file_path);

    bool removal_successful = fremove(&file);
    ASSERT_TRUE(removal_successful);

    bool copy_exists = fexists(&file);
    ASSERT_FALSE(copy_exists);

    GenericFile orig = GenericFile(file_path);

    bool orig_exists = fexists(&orig);
    ASSERT_TRUE(orig_exists);
}

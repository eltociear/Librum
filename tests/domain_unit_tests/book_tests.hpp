#pragma once
#include <gtest/gtest.h>
#include <QString>
#include "book.hpp"
#include "tag.hpp"


using namespace domain::models;


TEST(ABook, SucceedsAddingATag)
{
    // Arrange
    Book book("SomeBook", "SomeAuthor", "some/path");
    Tag tag("SomeTag");
    
    // Act
    auto result = book.addTag(tag);
    
    // Assert
    EXPECT_TRUE(result);
    EXPECT_EQ(1, book.getTags().size());
    EXPECT_EQ(tag.getName(), book.getTags()[0].getName());
}

TEST(ABook, FailsAddingATagIfItAlreadyExists)
{
    // Arrange
    Book book("SomeBook", "SomeAuthor", "some/path");
    Tag tag("SomeTag");
    
    // Act
    book.addTag(tag);  // First time added
    auto result = book.addTag(tag);  // Second time added
    
    // Assert
    EXPECT_FALSE(result);
}



TEST(ABook, SucceedsRemovingATag)
{
    // Arrange
    Book book("SomeBook", "SomeAuthor", "some/path");
    Tag tag("SomeTag");
    
    // Act
    book.addTag(tag);
    int prevAmountOfTags = book.getTags().size();
    
    auto result = book.removeTag(tag.getName());
    
    // Assert
    EXPECT_EQ(prevAmountOfTags - 1, book.getTags().size());
    EXPECT_TRUE(result);
}

TEST(ABook, FailsRemovingATagIfTagDoesNotExist)
{
    // Arrange
    Book book("SomeBook", "SomeAuthor", "some/path");
    Tag tag("SomeTag");
    
    // Act
    book.addTag(tag);
    
    auto result = book.removeTag(Tag("NonExistentTag"));
    
    // Assert
    EXPECT_FALSE(result);
}



TEST(ABook, SucceedsGettingAllTags)
{
    // Arrange
    Book book("SomeBook", "SomeAuthor", "some/path");
    Tag firstTag("FirstTag");
    Tag secondTag("SecondTag");
    Tag thirdTag("ThirdTag");
    
    // Act
    book.addTag(firstTag);
    book.addTag(secondTag);
    book.addTag(thirdTag);
    
    // Assert
    EXPECT_EQ(firstTag, book.getTags()[0]);
    EXPECT_EQ(secondTag, book.getTags()[1]);
    EXPECT_EQ(thirdTag, book.getTags()[2]);
}



TEST(ABook, SucceedsUpdatingBook)
{
    // Arrange
    Book book("SomeBook", "SomeAuthor", "SomePath", QImage("SomeCover"));
    
    Tag tag("SomeTag");
    Book bookToUpdateWith("SomeUpdatedBook", "SomeUpdatedAuthor",
                          "SomeUpdatedPath", QImage("SomeUpdatedCover"));
    bookToUpdateWith.addTag(tag);
    
    auto expectedResult = bookToUpdateWith;
    
    // Act
    book.update(bookToUpdateWith);
    
    // Assert
    EXPECT_EQ(expectedResult.getTitle(), book.getTitle());
    EXPECT_EQ(expectedResult.getFilePath(), book.getFilePath());
    EXPECT_EQ(expectedResult.getCover(), book.getCover());
    EXPECT_EQ(expectedResult.getTags()[0], book.getTags()[0]);
}
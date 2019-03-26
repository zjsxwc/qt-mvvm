#include "google_test.h"
#include "test_utils.h"
#include "sessionitemtag.h"
#include "sessionitem.h"

using namespace ModelView;

//! Tests for SessionItemTag class.

class TestSessionItemTag : public ::testing::Test
{
public:
    ~TestSessionItemTag();
};

TestSessionItemTag::~TestSessionItemTag() = default;

//! Initial state of emty SessionItemTag.

TEST_F(TestSessionItemTag, initialState)
{
    const std::string name("tag");
    SessionItemTag tag(TagInfo::universalTag(name));

    EXPECT_EQ(tag.childrenCount(), 0);
    EXPECT_EQ(tag.name(), name);
    EXPECT_EQ(tag.children(), std::vector<SessionItem*>());
}

//! Checking ::insertItem.

TEST_F(TestSessionItemTag, insertItem)
{
    const std::string tag_name("tag");
    SessionItemTag tag(TagInfo::universalTag(tag_name));

    // inserting non-existing item is not allowed
    EXPECT_FALSE(tag.insertItem(nullptr));
    EXPECT_EQ(tag.childrenCount(), 0);

    // insertion at the end
    SessionItem* child1 = new SessionItem;
    SessionItem* child2 = new SessionItem;
    EXPECT_TRUE(tag.insertItem(child1));
    EXPECT_TRUE(tag.insertItem(child2));
    EXPECT_EQ(tag.childrenCount(), 2);
    std::vector<SessionItem*> expected = {child1, child2};
    EXPECT_EQ(tag.children(), expected);

    // insertion at the beginning
    SessionItem* child3 = new SessionItem;
    EXPECT_TRUE(tag.insertItem(child3, 0));
    expected = {child3, child1, child2};
    EXPECT_EQ(tag.children(), expected);

    // insertion in between
    SessionItem* child4 = new SessionItem;
    EXPECT_TRUE(tag.insertItem(child4, 1));
    expected = {child3, child4, child1, child2};
    EXPECT_EQ(tag.children(), expected);

    // using index equal to number of items
    SessionItem* child5 = new SessionItem;
    EXPECT_TRUE(tag.insertItem(child5, tag.childrenCount()));
    expected = {child3, child4, child1, child2, child5};
    EXPECT_EQ(tag.children(), expected);
}

//! Checking ::insertItem when item has specific model type.

TEST_F(TestSessionItemTag, insertItemModelType)
{
    const std::string tag_name("tag");
    const std::vector<std::string> model_types = {"model_a"};

    SessionItemTag tag(TagInfo::universalTag(tag_name, model_types));

    // insertion of wrong model type is not allowed
    SessionItem* child1 = new SessionItem("model_a");
    SessionItem* child2 = new SessionItem("model_b");
    EXPECT_TRUE(tag.insertItem(child1));
    EXPECT_FALSE(tag.insertItem(child2));
    delete child2;

    std::vector<SessionItem*> expected = {child1};
    EXPECT_EQ(tag.children(), expected);
}

//! Checking ::insertItem when tag is related to property tag.

TEST_F(TestSessionItemTag, insertItemPropertyType)
{
    const std::string name("tag");
    const std::string property_type("Property");

    SessionItemTag tag(TagInfo::propertyTag(name, property_type));

    // insertion of second property item is not allowed (because of reached maximum)
    SessionItem* child1 = new SessionItem(property_type);
    SessionItem* child2 = new SessionItem(property_type);
    EXPECT_TRUE(tag.insertItem(child1));
    EXPECT_FALSE(tag.insertItem(child2));
    delete child2;

    // insertion of wrong model type is not allowed
    SessionItem* child3 = new SessionItem("another_model");
    EXPECT_FALSE(tag.insertItem(child3));
    delete child3;
    std::vector<SessionItem*> expected = {child1};
    EXPECT_EQ(tag.children(), expected);
}

//! Checking ::indexOfChild.

TEST_F(TestSessionItemTag, indexOfChild)
{
    const std::string tag_name("tag");
    const std::string model_type("model_a");

    SessionItemTag tag(TagInfo::universalTag(tag_name));

    // index of two items
    SessionItem* child1 = new SessionItem(model_type);
    SessionItem* child2 = new SessionItem(model_type);
    EXPECT_TRUE(tag.insertItem(child1));
    EXPECT_EQ(tag.indexOfChild(child1), 0);
    EXPECT_TRUE(tag.insertItem(child2));
    EXPECT_EQ(tag.indexOfChild(child1), 0);
    EXPECT_EQ(tag.indexOfChild(child2), 1);

    // not existing items
    EXPECT_EQ(tag.indexOfChild(nullptr), -1);
    std::unique_ptr<SessionItem> child3 = std::make_unique<SessionItem>(model_type);
    EXPECT_EQ(tag.indexOfChild(child3.get()), -1);
}





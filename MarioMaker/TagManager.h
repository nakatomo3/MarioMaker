#pragma once
#include <vector>
enum Tag {
	UNTAGGED,
	MANAGER,
	PLAYER,
	GROUND_BLOCK,
	BLOCK,
	HATENA_BLOCK,
	MUSHROOM,
	FLOWER,
	//ここにタグを追加、数字を指定しないでください
	TAG_LAST
};
class TagManager {
private:
	static std::vector<Tag> tagList;

public:
	static void Init();
	static std::vector<Tag> GetTagList();
	static bool ExistTag(Tag _tag);
};
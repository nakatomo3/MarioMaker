#include "TagManager.h"

std::vector<Tag> TagManager::tagList;

void TagManager::Init() {
	for (unsigned int i = 0; i < TAG_LAST; i++) {
		tagList.emplace_back((Tag)i);
	}
}

std::vector<Tag> TagManager::GetTagList() {
	return tagList;
}

bool TagManager::ExistTag(Tag _tag) {
	for (unsigned int i = 0; i < TAG_LAST; i++) {
		if (tagList[i] == _tag) {
			return true;
		}
	}
	return false;
}

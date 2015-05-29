#include "mm_utils.h"

using namespace mirror::ui;

unsigned int mirror::ui::UIUtils::idIndex = 0;

std::string mirror::ui::UIUtils::newId()
{
	char buffer[10];
	std::string id("UI_");
	UIUtils::idIndex++;
	sprintf_s(buffer, 10, "%d", UIUtils::idIndex);
	id.append(buffer);
	return id;
}

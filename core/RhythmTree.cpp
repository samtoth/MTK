//
// Created by samt on 02/06/2020.
//

#include "RhythmTree.h"
#include <algorithm>

float MTK::Core::RhythmTreeNode::getLength() {
	return (float)num/(float)denom;
}
MTK::Core::RhythmTreeNode MTK::Core::RhythmTreeNode::parseTree(std::string tree) {
	//tree.erase (std::remove_if(tree.begin(), tree.end(), isspace), tree.end());
}

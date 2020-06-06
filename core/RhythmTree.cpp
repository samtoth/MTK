//
// Created by samt on 02/06/2020.
//

#include "RhythmTree.h"
#include <algorithm>

namespace MTK::Core {
	float RhythmTreeNode::getLength() {
		return (float)num / (float)denom;
	}

	RhythmTreeNode::RhythmTreeNode(std::string tree) {
		tree.erase (std::remove_if(tree.begin(), tree.end(), isspace), tree.end());
	}
}
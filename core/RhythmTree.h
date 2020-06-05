//
// Created by samt on 02/06/2020.
//

//	RhythmTree file example
//	{ {a, b, c, d},   {a:b, a, c, d},    {a+, b+, c:d, e+:g-},   {a, b, c},     4{a, b, c}  }
//	  bar of 4/4    '' a:b is a dyad of a+b   a+ is a# g- is g flat  bar of 3/4  bar of 4/4 triplet
//  EBNF Syntax:
//	pitch ::= 'a-g' >> (*(+) / *(-))
//	unit  ::= pitch >> *(':' >> pitch)
//	pregroup ::= int >> -('/' >> int)
//	group ::= -pregroup >> '{' >> unit >> *(',' >> unit) >> '}'

#ifndef MUSICTOOLKIT_RHYTHMTREE_H
#define MUSICTOOLKIT_RHYTHMTREE_H

#include <vector>
#include <string>
#include <tao/pegtl.hpp>

namespace MTK::Core {
	class RhythmTreeNode {
	public:
		RhythmTreeNode() = default;
		~RhythmTreeNode(){
			for(auto *child : children){
				delete child;
			}
		}

		std::vector<RhythmTreeNode*> children;
		float getLength();


		static RhythmTreeNode parseTree(std::string tree);
	protected:
		int num;
		int denom;
	};

	class RhythmTreeLeaf : public RhythmTreeNode {

	};
}
#endif //MUSICTOOLKIT_RHYTHMTREE_H

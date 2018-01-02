// **************************************************************
// *		   
// *  quadtree.h
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

class Quadtree
{
	public:
	Quadtree( );	
	Quadtree( const PNG & source, int resolution );	
	Quadtree( Quadtree const & other);	
	~Quadtree( );
	const Quadtree & operator= ( const Quadtree & source );
	void buildTree( const PNG & source, int resolution );
	PNG decompress( ) const;
	RGBAPixel getPixel	( int x, int y ) const;
	void clockwiseRotate();
	void prune(int tolerance);
	int pruneSize(int tolerance) const;
	int idealPrune(int number_of_leaves) const;


	private:

	int part;
	class QuadtreeNode
	{
		public:
		QuadtreeNode();
		QuadtreeNode(RGBAPixel const & elem);
		QuadtreeNode* nwChild;  // pointer to northwest child
		QuadtreeNode* neChild;  // pointer to northeast child
		QuadtreeNode* swChild;  // pointer to southwest child
		QuadtreeNode* seChild;  // pointer to southeast child

		RGBAPixel element;  // the pixel stored as this node's "data"
	};
	
	QuadtreeNode* root;    // pointer to root of quadtree
	void clear(QuadtreeNode *& current_node);
	void copy(Quadtree const & other,QuadtreeNode*&mynode, QuadtreeNode *const &rootnode);
	void buildTreehelper(QuadtreeNode *& mynode,const PNG & source, int resolution, int x, int y);
	void getPixelhelper(int x,int y,int partition,QuadtreeNode* curr,int currx, int curry,RGBAPixel&mine)const;
	void decompresshelper(	QuadtreeNode*const& mynode,int partition, int x, int y,PNG & my)const;
	RGBAPixel calcaverage(RGBAPixel a,RGBAPixel b,RGBAPixel c,RGBAPixel d);
	void clockwiseRotateHelper( QuadtreeNode *& current);
	void pruneHelper(int tolerance, QuadtreeNode *& current);
	void innerPruneHelper(int tolerance, QuadtreeNode * const & current, RGBAPixel elm1, bool & to_destroy) const;
	int pruneSizeHelper( int tolerance, QuadtreeNode * current, int & temp) const;
	int idealPruneHelper(int number_of_leaves, int tolerance, int low, int high) const;


	
	#include "quadtree_given.h"

};

#endif
// **************************************************************
// *		   
// *  quadtree.cpp
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#include "quadtree.h"
#include "iostream"
#include <math.h>

using namespace std;

Quadtree::Quadtree()	
{
	
	root=NULL;
}
Quadtree::Quadtree(const PNG & 	source,int resolution)	
{
	//'root = new QuadtreeNode();
	root = NULL;
	part= resolution;
	buildTree(source,resolution);
}
Quadtree::QuadtreeNode::QuadtreeNode()
{
	nwChild=NULL;
	neChild=NULL;
	swChild=NULL;
	seChild=NULL;
	RGBAPixel r;
	element=r;

	
}
Quadtree::QuadtreeNode::QuadtreeNode(RGBAPixel const & elem)
{
	nwChild=NULL;
	neChild=NULL;
	swChild=NULL;
	seChild=NULL;
	element=elem;

	
}
Quadtree::Quadtree(Quadtree const & other)
{
	root= NULL;
	part=other.part;
	copy( other,root, other.root );
}
Quadtree::~Quadtree()
{
	clear(root);
}
const Quadtree & Quadtree::operator=(Quadtree const & source)
{
	if( this != & source)
	{
		clear(root);
		copy(source, root, source.root);
		part= source.part;

	}
	return *this;
}	

RGBAPixel Quadtree::getPixel(int x,int y)const
{
	RGBAPixel self;
	getPixelhelper(x, y, part, root, 0, 0, self);
	return self;
}

void Quadtree::getPixelhelper(int x, int y, int partition, QuadtreeNode* curr, int currx, int curry, RGBAPixel & currentNode) const
{
	if(curr->nwChild==NULL&&curr->neChild==NULL&&curr->swChild==NULL&&curr->seChild==NULL)
	{
		
			if( currx==x&&curry==y)
			{
				currentNode = curr->element;
			}
	
	}
	else
	{

		if(x < ( currx + partition / 2 ) && y < ( curry + partition / 2 ) )
		{
			getPixelhelper(x, y, partition / 2, curr -> nwChild, currx, curry, currentNode );
		}

		if(x >= ( currx + partition / 2 ) && y < ( curry + partition / 2 ) )
		{
			getPixelhelper(x, y, partition / 2, curr -> neChild, currx + partition / 2, curry, currentNode);
		}

		if(x < ( currx + partition / 2 ) && y >= ( curry + partition / 2 ) )
		{
			getPixelhelper(x, y, partition/2, curr->swChild, currx,curry + partition / 2, currentNode);
		}

		if(x >= (currx + partition / 2 ) && y >= ( curry + partition / 2 ) )
		{
			getPixelhelper(x, y, partition/2, curr -> seChild, currx + partition/2, curry+partition/2, currentNode);
		}
	}
}

void Quadtree::clear(QuadtreeNode *& current_node)
{
	if(current_node==NULL)
	{
		return;
	}
	else if( current_node -> nwChild == NULL && current_node -> neChild == NULL && current_node -> swChild == NULL && current_node -> seChild == NULL)
	{
		delete current_node;
		current_node = NULL;
	}
	else
	{
		QuadtreeNode *t1= current_node->nwChild;
		QuadtreeNode *t2= current_node->neChild;
		QuadtreeNode *t3= current_node->swChild;
		QuadtreeNode *t4= current_node->seChild;
		delete current_node;
		current_node= NULL;
		clear(t1);
		clear(t2);
		clear(t3);
		clear(t4);
		
	}
}

void Quadtree::copy(const Quadtree & other,  QuadtreeNode *& mynode, QuadtreeNode  * const&rootmynode)
{
	if( rootmynode==NULL)
	{
		return;
	}
	mynode=new QuadtreeNode(rootmynode->element);

	if( rootmynode->nwChild==NULL&&rootmynode->swChild==NULL&&rootmynode->neChild==NULL&&rootmynode->seChild==NULL)
	{
		
		return;
	}
	
		copy(other,mynode->nwChild,rootmynode->nwChild);
		copy(other,mynode->neChild,rootmynode->neChild);
		copy(other,mynode->swChild,rootmynode->swChild);
		copy(other,mynode->seChild,rootmynode->seChild);
	
}
void Quadtree::buildTree(const PNG & source, int resolution)
{
	clear(root);
	part=resolution;
	buildTreehelper(root,source,resolution,0,0);
}

void Quadtree::clockwiseRotate()
{
	if(root != NULL)
	{
		clockwiseRotateHelper(root);
	}
}

void Quadtree::prune(int tolerance)
{
	if( root != NULL)
	{
		pruneHelper( tolerance, root);
	}
}

int Quadtree::pruneSize( int tolerance ) const
{
	int temp;
	if(root == NULL)
	{
		return 0;
	}
	else
	{
		return pruneSizeHelper(tolerance, root, temp);
	}
}

int Quadtree::idealPrune( int number_of_leaves) const
{
	int maxthreshold = pow(255, 2) * 3;
	int current_threshold = idealPruneHelper(number_of_leaves, maxthreshold / 2, 0, maxthreshold);
	return current_threshold;
}

int Quadtree::idealPruneHelper(int number_of_leaves, int tolerance, int low, int high) const
{
	if(low > high || low == high)
	{
		return high;
	}

	int midpoint = (high + low) / 2;
	int size = pruneSize(midpoint);

	if (size <= number_of_leaves)
	{
		return idealPruneHelper(number_of_leaves, tolerance / 2, low, midpoint);
	}
	else
	{
		return idealPruneHelper(number_of_leaves, tolerance / 2, midpoint + 1, high);
	}
}

int Quadtree::pruneSizeHelper( int tolerance, QuadtreeNode * current, int & temp) const
{
	if( current -> nwChild == NULL && current -> neChild == NULL && current -> swChild == NULL && current -> seChild)
	{
		return 1;
	}
	else
	{
		bool to_destroy = true;
		innerPruneHelper( tolerance, current, current -> element, to_destroy);
		if(to_destroy == true)
		{
			return 1;
		}
		else
		{
			return pruneSizeHelper(tolerance, current -> nwChild, temp) + pruneSizeHelper(tolerance, current -> neChild, temp) + pruneSizeHelper(tolerance, current -> swChild, temp) + pruneSizeHelper(tolerance, current -> seChild, temp);
		}
	}
}

void Quadtree::pruneHelper(int tolerance, QuadtreeNode *& current)
{
	if(current -> nwChild == NULL && current -> neChild == NULL && current -> swChild == NULL && current -> seChild == NULL)
	{
		return;
	}
	else
	{
		bool to_destroy = true;
		innerPruneHelper(tolerance, current, current -> element, to_destroy);
		if (to_destroy == true)
		{
			clear( current -> nwChild );
			clear( current -> neChild );
			clear( current -> swChild );
			clear( current -> seChild );
			current -> neChild = NULL;
			current -> nwChild = NULL;
			current -> seChild = NULL;
			current -> swChild = NULL;
			return;
		}
		pruneHelper( tolerance, current -> nwChild );
		pruneHelper( tolerance, current -> neChild );
		pruneHelper( tolerance, current -> swChild );
		pruneHelper( tolerance, current -> seChild );
	}
}

void Quadtree::innerPruneHelper(int tolerance, QuadtreeNode * const & current, RGBAPixel elm1, bool & to_destroy) const
{
	if (current -> nwChild == NULL && current -> neChild == NULL && current -> swChild == NULL && current -> seChild == NULL)
	{
		RGBAPixel elm2 = current -> element;
		bool toleranceFinder;
		// Finding tolerance
		int tol = pow((elm1.red - elm2.red), 2) + pow((elm1.green - elm2.green), 2) + pow((elm1.blue - elm2.blue), 2);
		if (tol <= tolerance)
		{
			toleranceFinder = true;
		}
		else
		{
			toleranceFinder = false;
		}

		if (!toleranceFinder)
		{
			to_destroy = false;
		}
	}
	else
	{
		innerPruneHelper(tolerance, current -> nwChild, elm1, to_destroy);
		innerPruneHelper(tolerance, current -> neChild, elm1, to_destroy);
		innerPruneHelper(tolerance, current -> swChild, elm1, to_destroy);
		innerPruneHelper(tolerance, current -> seChild, elm1, to_destroy);
	}
}

void Quadtree::clockwiseRotateHelper( QuadtreeNode *& current)
{
	// Base Case
	if( current -> nwChild == NULL && current -> neChild == NULL && current -> swChild == NULL && current -> seChild == NULL)
	{
		return;
	}
	else
	{
		QuadtreeNode * temporary = current -> nwChild;
		current -> nwChild = current -> swChild;
		current ->swChild = current -> seChild;
		current -> seChild = current -> neChild;
		current -> neChild = temporary;
		clockwiseRotateHelper(current -> nwChild);
		clockwiseRotateHelper(current -> neChild);
		clockwiseRotateHelper(current -> swChild);
		clockwiseRotateHelper(current -> seChild);
	}
}

void Quadtree::buildTreehelper(QuadtreeNode *& mynode,const PNG & source, int resolution, int x, int y)
{
	if(resolution==1)
	{
		mynode= new QuadtreeNode();
		mynode->element=(*source(x,y));

	}
	else
	{
		mynode= new QuadtreeNode();
		buildTreehelper(mynode->nwChild,source,resolution/2,x,y);//keep recursing down the tree
		buildTreehelper(mynode->neChild,source,resolution/2,x+(resolution/2),y);
		buildTreehelper(mynode->swChild,source,resolution/2,x,y+(resolution/2));
		buildTreehelper(mynode->seChild,source,resolution/2,x+(resolution/2),y+(resolution/2));
		mynode->element= calcaverage(mynode->swChild->element,mynode->nwChild->element,mynode->seChild->element,mynode->neChild->element);

	}
}

RGBAPixel Quadtree::calcaverage(RGBAPixel a,RGBAPixel b,RGBAPixel c,RGBAPixel d)
{
        int red = (a.red+b.red+c.red+d.red)/4;
        int blue = (a.blue+b.blue+c.blue+d.blue)/4;
        int green = (a.green+b.green+c.green+d.green)/4;
        RGBAPixel r(red,green,blue);
        return r;
}

PNG Quadtree::decompress() const
{
	PNG data(part,part);
	decompresshelper(root,part,0,0,data);
	return data;
}

void Quadtree::decompresshelper (QuadtreeNode * const & mynode, int resolution, int x, int y, PNG & my) const
{
	if(resolution==1)
	{
		*my(x,y)= mynode->element;
		return;
	}
	else
	{
		if(mynode->nwChild==NULL)
		{
			for (int i = x; i < (x+resolution); ++i)
			{
				for (int j = y; j < (y+resolution); ++j)
				{
					*my(i,j)=mynode->element;
				}
			}
			return;
		}
			decompresshelper(mynode->nwChild,resolution/2,x,y,my);
			decompresshelper(mynode->neChild,resolution/2,x+(resolution/2),y,my);
			decompresshelper(mynode->swChild,resolution/2,x,y+(resolution/2),my);
			decompresshelper(mynode->seChild,resolution/2,x+(resolution/2),y+(resolution/2),my);
	}
}


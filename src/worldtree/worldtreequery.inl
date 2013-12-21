#pragma once

#include <cassert>

#include <worldtree/worldtree.h>
#include <worldtree/worldtreenode.h>
#include <worldtree/worldtreegeode.h>
#include <worldobject/worldobject.h>


template<typename Shape>
WorldTreeQuery<Shape>::WorldTreeQuery(WorldTree* worldTree, const Shape& shape):
    m_worldTree(worldTree),
    m_nodeHint(nullptr),
    m_collideableWith(nullptr),
    m_shape(shape)
{

}

template<typename Shape>
void WorldTreeQuery<Shape>::setNodeHint(WorldTreeNode* nodeHint) {
    m_nodeHint = nodeHint;
}

template<typename Shape>
void WorldTreeQuery<Shape>::setCollidableWith(WorldObject* worldObject) {
    m_collideableWith = worldObject;
}

template<typename Shape>
bool WorldTreeQuery<Shape>::areGeodesIntersecting() const {

}

template<typename Shape>
std::set<WorldTreeGeode*> WorldTreeQuery<Shape>::intersectingGeodes() const {

}

template<typename Shape>
bool WorldTreeQuery<Shape>::areVoxelsIntersecting() const {

}

template<typename Shape>
std::set<Voxel*> WorldTreeQuery<Shape>::intersectingVoxels() const {

}

template<typename Shape>
bool WorldTreeQuery<Shape>::areWorldObjectsIntersecting() const {

}

template<typename Shape>
std::set<Voxel*> WorldTreeQuery<Shape>::intersectingVoxels() const {

}

template<typename Shape>
template<typename QueryResult, QueryResult (*queryFunc)(WorldTreeNode*)>
QueryResult WorldTreeQuery<Shape>::query() {
    if (m_nodeHint == nullptr) {
        return queryFunc(m_worldTree);
    }
    else {
        if (m_nodeHint->aabb().contains(m_shape)) {
            return queryFunc(m_nodeHint);
        }
        else if(m_nodeHint->parent() != nullptr) {
            m_nodeHint = m_nodeHint->parent()
            return query<QueryResult, queryFunc>();
        }
        else {
            assert(m_worldTree == m_nodeHint);
            return queryFunc(m_worldTree);
        }
    }
}

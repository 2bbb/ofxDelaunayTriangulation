//
//  ofxDelaunayTriangulation.h
//  delaunays
//
//  Created by 2bit on 2020/03/07.
//

#ifndef ofxDelaunayTriangulation_h
#define ofxDelaunayTriangulation_h

#include "vector2.h"
#include "triangle.h"
#include "delaunay.h"

struct ofxDelaunayTriangulation {
    void addPoint(double x, double y)
    { points.emplace_back(x, y); };
    template <typename vector_type>
    inline void addPoint(const vector_type &v)
    { addPoint(v.x, v.y); };
    
    inline void clear() {
        points.clear();
        triangles.clear();
        edges.clear();
    }
    
    inline void triangulate() {
        triangles = triangulation.triangulate(points);
        edges = triangulation.getEdges();
    }
    
    inline std::size_t getNumPoints() const
    { return points.size(); };
    
    inline std::size_t getNumTriangles() const
    { return triangles.size(); };
    
    inline std::size_t getNumEdges() const
    { return edges.size(); };
    
    ofVec3f getPointAt(std::size_t index) const {
        return ofVec3f(points[index].x, points[index].y, 0);
    }
    
    std::vector<ofVec3f> getEdgeAt(std::size_t index) const {
        const auto &edge = edges[index];
        return { toOF(edge.v), toOF(edge.w) };
    }
    
    std::vector<ofVec3f> getTriangleAt(std::size_t index) const {
        const auto &tri = triangles[index];
        return { toOF(tri.a), toOF(tri.b), toOF(tri.c) };
    }
    
    inline void draw() const {
        for(auto i = 0; i < getNumPoints(); ++i) {
            ofDrawCircle(getPointAt(i), 5);
        }
        for(auto i = 0; i < getNumEdges(); ++i) {
            auto &&edge = getEdgeAt(i);
            ofDrawLine(edge[0], edge[1]);
        }
    }
    
protected:
    inline static ofVec3f toOF(const Vector2 * const v) {
        return ofVec3f(v->x, v->y, 0.0);
    }
    
    std::vector<Vector2> points;
    std::vector<Triangle> triangles;
    std::vector<Edge> edges;
    Delaunay triangulation;
};

#endif /* ofxDelaunayTriangulation_h */

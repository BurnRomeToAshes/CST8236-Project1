#ifndef _TRANSFORM_NODE_H_
#define _TRANSFORM_NODE_H_

#include <SFML/Graphics.hpp>

#include <vector>
using std::vector;

class TransformNode
{
public:
  TransformNode(sf::Shape *shape);
  TransformNode();

  bool AddChild(TransformNode *child);
  bool RemoveChild(TransformNode *child);
  bool HasChild(TransformNode *child);

  void Draw(sf::RenderTarget *target, sf::Transform parentTransform = sf::Transform::Identity);

protected:
  std::vector<TransformNode *> m_Children;
  TransformNode *m_Parent;

  sf::Shape *m_Shape;
};


#endif
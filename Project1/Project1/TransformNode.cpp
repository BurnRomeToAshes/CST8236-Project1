#include "TransformNode.h"

TransformNode::TransformNode(sf::Shape *shape) : m_Shape(shape) {}

TransformNode::TransformNode()
{
}

bool TransformNode::AddChild(TransformNode *child) {
  bool didAdd = false;
  bool hasChild = HasChild(child);
  if (child != nullptr && child != this && !hasChild) {
    // Add the child to our vector.
    m_Children.push_back(child);
    child->m_Parent = this;
    didAdd = true;
  }

  return didAdd;
}

bool TransformNode::RemoveChild(TransformNode *child) {
  bool didRemove = false;

  // TODO: add recursive check.
  auto itr = std::find(m_Children.begin(), m_Children.end(), child);

  if (itr != m_Children.end()) {
    // Remove that child!
    m_Children.erase(itr);
    child->m_Parent = nullptr;
    didRemove = true;
  }

  return didRemove;
}

bool TransformNode::HasChild(TransformNode *child) {
  // TODO: add recursive check.
  auto itr = std::find(m_Children.begin(), m_Children.end(), child);

  return (itr != m_Children.end());
}

void TransformNode::Draw(sf::RenderTarget *target, sf::Transform parentTransform) {

  target->draw(*m_Shape, parentTransform);
  sf::Transform hierarchy = parentTransform * m_Shape->getTransform();

  for (int childIndex = 0; childIndex < m_Children.size(); childIndex++) {
    m_Children[childIndex]->Draw(target, hierarchy);
  }

}
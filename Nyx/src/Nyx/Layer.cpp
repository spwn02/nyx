#include "nyxpch.h"
#include "Layer.h"

namespace Nyx {
  Layer::Layer(const std::string& debugName)
    : m_debugName(debugName) { }

  Layer::~Layer() {}
}
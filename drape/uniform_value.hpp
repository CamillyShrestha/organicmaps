#pragma once

#include "pointers.hpp"
#include "gpu_program.hpp"

#include "../std/string.hpp"
#include "../std/shared_array.hpp"

class UniformValue
{
public:
  explicit UniformValue(const string & name, int32_t v);
  explicit UniformValue(const string & name, int32_t v1, int32_t v2);
  explicit UniformValue(const string & name, int32_t v1, int32_t v2, int32_t v3);
  explicit UniformValue(const string & name, int32_t v1, int32_t v2, int32_t v3, int32_t v4);

  explicit UniformValue(const string & name, float v);
  explicit UniformValue(const string & name, float v1, float v2);
  explicit UniformValue(const string & name, float v1, float v2, float v3);
  explicit UniformValue(const string & name, float v1, float v2, float v3, float v4);

  explicit UniformValue(const string & name, float * matrixValue);

  void Apply(ReferencePoiner<GpuProgram> program);

  bool operator<(const UniformValue & other) const
  {
    size_t s = ((m_type == Int) ? sizeof(int32_t) : sizeof(float)) * m_componentCount;
    return m_name < other.m_name
        || m_type < other.m_type
        || m_componentCount < other.m_componentCount
        || memcmp(m_values.get(), other.m_values.get(), s);
  }

private:
  void Allocate(size_t byteCount);

  template <typename T>
  T * CastMemory()
  {
    return reinterpret_cast<T *>(m_values.get());
  }

private:
  enum Type
  {
    Int,
    Float,
    Matrix4x4
  };

  string m_name;
  Type m_type;
  size_t m_componentCount;

  shared_array<uint8_t> m_values;
};

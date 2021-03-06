#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>

namespace Emu {

class Memmap {
public:
  bool AllocateSHMRegion(size_t Size);
  void DeallocateSHMRegion();

  void *MapRegion(size_t Offset, size_t Size);
  void UnmapRegion(void *Ptr, size_t Size);

  void *GetPointer(uint64_t Offset);

  template<typename T>
  T GetPointer(uint64_t Offset) {
    return reinterpret_cast<T>(GetPointer(Offset));
  }

  struct MemRegion {
    void *Ptr;
    size_t Offset;
    size_t Size;

    bool operator==(void* rhs) { return Ptr == rhs; }
  };

  std::vector<MemRegion> MappedRegions;

private:
  int SHMfd;
  size_t SHMSize;
  void *Base{};
};
}

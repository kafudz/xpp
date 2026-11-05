#ifndef X_VALUEPARAM_HPP
#define X_VALUEPARAM_HPP

#include <cstdint>
#include <map>
#include <vector>

namespace xpp {

class valueparam {
  public:
    valueparam &
    set(const uint32_t & bit, const uint32_t & value)
    {
      m_has_changed = true;
      m_mask |= bit;
      m_values_map[bit] = value;
      return *this;
    }

    uint32_t
    mask(void) const
    {
      return m_mask;
    }

    // The values are ordered by their bit, as required by the X protocol.
    uint32_t *
    values(void)
    {
      // Only rebuild the cache when something changed. Previously the values
      // were appended on every call, so repeated calls grew the vector with
      // duplicates.
      if (m_has_changed) {
        m_values.clear();

        for (const auto & item : m_values_map) {
          m_values.push_back(item.second);
        }

        m_has_changed = false;
      }

      return m_values.data();
    }

  private:
    bool m_has_changed = true;
    uint32_t m_mask = 0;
    std::vector<uint32_t> m_values;
    std::map<uint32_t, uint32_t> m_values_map;
};

} // namespace xpp

#endif // X_VALUEPARAM_HPP

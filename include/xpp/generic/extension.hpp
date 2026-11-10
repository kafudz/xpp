#ifndef XPP_GENERIC_EXTENSION_HPP
#define XPP_GENERIC_EXTENSION_HPP

#include <stdexcept> // runtime_error
#include <xcb/xcb.h>

namespace xpp { namespace generic {

template<typename Derived, xcb_extension_t * Id>
class extension
{
  public:
    extension(xcb_connection_t * const c)
      : m_c(c)
    {
      prefetch();
    }

    const xcb_query_extension_reply_t &
    operator*(void) const
    {
      return *checked();
    }

    const xcb_query_extension_reply_t *
    operator->(void) const
    {
      return checked();
    }

    operator const xcb_query_extension_reply_t *(void) const
    {
      return m_extension;
    }

    Derived &
    get(void)
    {
      m_extension = xcb_get_extension_data(m_c, Id);
      return static_cast<Derived &>(*this);
    }

    Derived &
    prefetch(void)
    {
      xcb_prefetch_extension_data(m_c, Id);
      return static_cast<Derived &>(*this);
    }

  private:
    // xcb returns no extension data when the connection has an error (or
    // get() was not called yet); throw instead of dereferencing a null pointer.
    const xcb_query_extension_reply_t *
    checked(void) const
    {
      if (m_extension == nullptr) {
        throw std::runtime_error("no extension data available "
                                 "(connection error or get() not called)");
      }
      return m_extension;
    }

    xcb_connection_t * m_c = nullptr;
    // The result must not be freed.
    // This storage is managed by the cache itself.
    const xcb_query_extension_reply_t * m_extension = nullptr;
}; // class extension

} } // namespace xpp::generic

#endif // XPP_GENERIC_EXTENSION_HPP

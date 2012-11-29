/**
 * @file NonCopyable.hpp
 * @date 29. nov. 2012
 * @author Johan Klokkhammer Helsing
 */
#ifndef NONCOPYABLE_HPP
#define NONCOPYABLE_HPP

namespace helsing {

/** @brief base class that represents something that may not be copied
 */
struct NonCopyable {
	NonCopyable() = default;
	NonCopyable(const NonCopyable&) = delete;
	NonCopyable & operator=(const NonCopyable&) = delete;
};

} // namespace helsing

#endif // NONCOPYABLE_HPP



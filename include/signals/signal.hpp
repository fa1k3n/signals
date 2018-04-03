#ifndef __SIGNAL_HPP__
#define __SIGNAL_HPP__

#include <boost/signals2.hpp>
#include <functional>

#define emit

namespace Signals {
	template <typename... T> using signal = typename boost::signals2::signal<void(T...)>;

	template < class SIGINST, class SIG, class SIGBASE, typename T, class... Args>
	auto connect( SIGINST* sigi, SIG SIGBASE::* sig, T* sloti, void(T::*fun)(Args...)) {
		std::function<void(Args...)> conn_impl = [fun,sloti](Args... args){ 
			std::bind(fun, sloti, args...)();
		};
		return std::mem_fn(sig)(sigi).connect(conn_impl);
	}

            	template <class SIGINST, class SIG, class SIGBASE,  typename T, class... Args>
	auto connect(SIGINST* sigi, SIG SIGBASE::* sig, void(*fun)(Args...)) {
		std::function<void(Args...)> conn_impl = [fun](Args... args){ 
			std::bind(fun, args...)();
		};
		return std::mem_fn(sig)(sigi).connect(conn_impl);
	}

	template <class SIGINST, class SIG, class SIGBASE,  typename FUN>
	auto connect(SIGINST* sigi, SIG SIGBASE::* sig, FUN fun) {
		return std::mem_fn(sig)(sigi).connect(fun);
	}
}

#endif
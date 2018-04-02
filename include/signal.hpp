#ifndef __SIGNAL_HPP__
#define __SIGNAL_HPP__

#include <boost/signals2.hpp>
#include <functional>

#define emit

namespace Signals {
	template <typename... T> using signal = typename boost::signals2::signal<void(T...)>;

	template <class SIG, class SIGBASE, class SIGINST, typename T, class... Args>
	auto connect(SIG SIGBASE::* sig, SIGINST* sigi, void(T::*fun)(Args...), T* sloti) {
		std::function<void(Args...)> conn_impl = [fun,sloti](Args... args){ 
			std::bind(fun, sloti, args...)();
		};
		return std::mem_fn(sig)(sigi).connect(conn_impl);
	}


	template <class SIG, class SIGBASE, class SIGINST, typename FUN>
	auto connect(SIG SIGBASE::* sig, SIGINST* sigi, FUN fun) {
		return std::mem_fn(sig)(sigi).connect(fun);
	}
}

#endif
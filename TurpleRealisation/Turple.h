#pragma once

#include <utility>

//Ѕазовый шаблон класса (не инстанцируетс€)
template <typename... Args>
struct Tuple;

//ƒно рекурсии
template <>
struct Tuple<>
{};

//ќбеспечиваетс€ рекурси€ за счет передачи аргументов базовому классу
template <typename Head, typename... Tail>
struct Tuple<Head, Tail...> : Tuple<Tail...>
{
	typedef Tuple<Tail...> Base_type;
	typedef Head Value_type;

	Value_type head_;
	//ѕозвол€ет обеспечить доступ к базовому классу (так по цепочке)
	Base_type& base = static_cast<Base_type&>(*this);

	// онструктор, передающий параметру базовому классу
	Tuple(Head h, Tail... tail) : Tuple<Tail...>(tail...), head_(h) {}
};

template <int i, typename Head, typename... Tail>
struct Getter
{
	typedef typename Getter<i - 1, Head, Tail...>::return_type return_type;

	static return_type Get(Tuple<Head, Tail...> t)
	{
		return Getter(i - 1, Tail...)::Get(t);
	}
};

template <typename Head, typename... Tail>
struct Getter<0, Head, Tail...>
{
	typedef typename Tuple<Head, Tail...>::Value_type return_type;

	static return_type Get(Tuple<Head, Tail...> t)
	{
		return t.head_;
	}
};

template <int i, typename Head, typename... Tail>
typename Getter<i, Head, Tail...>::return_type
Get(Tuple<Head, Tail...> t)
{
	return Getter<i, Head, Tail...>::Get(t);
}

template <typename F, typename Tuple, int... n>
auto Call(F f, Tuple&& t)
{
	return f(std::get<n>(std::forward<Tuple>(t))...);
}

template <typename F, typename Tuple, bool enough, int totalArgs, int... n>
struct Call_impl
{
	auto static Call(F f, Tuple&& t)
	{
		return Call_impl<F, Tuple, totalArgs == 1 + sizeof...(n), totalArgs, n..., sizeof...(n)>
			::Call(f, std::forward<Tuple>(t));
	}
};

template <typename F, typename Tuple, int totalArgs, int... n>
struct Call_impl<F, Tuple, true, totalArgs, n...>
{
	auto Call(F f, Tuple&& t)
	{
		return f(std::get<n>(forward<Tuple>(t))...);
	}
};

template <typename F, typename Tuple>
auto Call(F f, Tuple&& t) 
{
	typedef typename std::decay<Tuple>::type type;
	return Call_impl<F, Tuple, 0 == std::tuple_size<type>::value, std::tuple_size<type>::value>
		::Call(f, std::forward<tuple>(t));
}
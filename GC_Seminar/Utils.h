//------------------------------------------------------------------------
//
//  Name:		Utils.h
//
//  Desc:		Some utility functions.
//
//  Author:		Insub Im (insooneelife@naver.com)
//
//------------------------------------------------------------------------

#pragma once

#include <SDL\SDL.h>

namespace
{
	//random number 积己扁
	template<unsigned int T = 0, unsigned int U = 1>
	static inline auto genRand() {
		static std::random_device rd;
		static std::mt19937 mt(rd());
		static std::uniform_real_distribution<double> dist(T, std::nextafter(U, DBL_MAX));

		return dist(mt);
	}

	//random number 积己扁 (备埃)  [T , U)  test
	template<typename T, typename U>
	static inline decltype(auto) random(T begin, U end) {
		double rand = genRand<0, 1>();
		return ((end - begin) * rand + begin);
	}

}
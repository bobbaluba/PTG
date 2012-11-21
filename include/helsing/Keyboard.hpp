/**
 * @file Keyboard.hpp
 * @date 21. nov 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

namespace helsing {

class Keyboard {
public:
	enum Key{
		UNKNOWN = -1,
		A = 0,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		NUMBER_0,
		NUMBER_1,
		NUMBER_2,
		NUMBER_3,
		NUMBER_4,
		NUMBER_5,
		NUMBER_6,
		NUMBER_7,
		NUMBER_8,
		NUMBER_9,
		ESCAPE,
		LEFT_CONTROL,
		LEFT_SHIFT,
		LEFT_ALT,
		LEFT_SUPER,
		RIGHT_SHIFT,
		RIGHT_CONTROL,
		RIGHT_ALT,
		RIGHT_SUPER,
		MENU,
		LEFT_BRACKET,
		RIGHT_BRACKET,
		SEMICOLON,
		COMMA,
		PERIOD,
		QUOTE,
		SLASH,
		BACKSLASH,
		TILDE,
		EQUAL,
		DASH,
		SPACE,
		RETURN,
		TAB,
		LEFT,
		RIGHT,
		UP,
		DOWN,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12
	};
};

} // namespace helsing
#endif // KEYBOARD_HPP

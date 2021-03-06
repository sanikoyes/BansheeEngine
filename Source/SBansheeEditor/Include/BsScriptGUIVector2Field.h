//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsScriptEditorPrerequisites.h"
#include "BsScriptGUIElement.h"

namespace BansheeEngine
{
	/** @addtogroup ScriptInteropEditor
	 *  @{
	 */

	/**	Interop class between C++ & CLR for GUIVector2Field. */
	class BS_SCR_BED_EXPORT ScriptGUIVector2Field : public TScriptGUIElement<ScriptGUIVector2Field>
	{
	public:
		SCRIPT_OBJ(EDITOR_ASSEMBLY, "BansheeEditor", "GUIVector2Field")

	private:
		/**
		 * Triggered when the value in the native vector field changes.
		 *
		 * @param[in]	instance	Managed GUIVector2Field instance.
		 * @param[in]	newValue	New vector value.
		 */
		static void onChanged(MonoObject* instance, const Vector2& newValue);

		/**
		 * Triggered when the user confirms input in the native vector field.
		 *
		 * @param[in]	instance	Managed GUIVector2Field instance.
		 */
		static void onConfirmed(MonoObject* instance);

		ScriptGUIVector2Field(MonoObject* instance, GUIVector2Field* vector2Field);

		/************************************************************************/
		/* 								CLR HOOKS						   		*/
		/************************************************************************/
		static void internal_createInstance(MonoObject* instance, MonoObject* title, UINT32 titleWidth,
			MonoString* style, MonoArray* guiOptions, bool withTitle);

		static void internal_getValue(ScriptGUIVector2Field* nativeInstance, Vector2* output);
		static void internal_setValue(ScriptGUIVector2Field* nativeInstance, Vector2* value);
		static void internal_hasInputFocus(ScriptGUIVector2Field* nativeInstance, bool* output);
		static void internal_setTint(ScriptGUIVector2Field* nativeInstance, Color* color);

		typedef void(__stdcall *OnChangedThunkDef) (MonoObject*, MonoObject*, MonoException**);
		typedef void(__stdcall *OnConfirmedThunkDef) (MonoObject*, MonoException**);

		static OnChangedThunkDef onChangedThunk;
		static OnConfirmedThunkDef onConfirmedThunk;
	};

	/** @} */
}
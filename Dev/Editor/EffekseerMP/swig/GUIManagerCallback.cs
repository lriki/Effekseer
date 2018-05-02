//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.12
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------

namespace Effekseer.swig {

public class GUIManagerCallback : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GUIManagerCallback(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(GUIManagerCallback obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~GUIManagerCallback() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          EffekseerNativePINVOKE.delete_GUIManagerCallback(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public GUIManagerCallback() : this(EffekseerNativePINVOKE.new_GUIManagerCallback(), true) {
    SwigDirectorConnect();
  }

  public virtual void Resized(int x, int y) {
    if (SwigDerivedClassHasMethod("Resized", swigMethodTypes0)) EffekseerNativePINVOKE.GUIManagerCallback_ResizedSwigExplicitGUIManagerCallback(swigCPtr, x, y); else EffekseerNativePINVOKE.GUIManagerCallback_Resized(swigCPtr, x, y);
  }

  public virtual void Droped() {
    if (SwigDerivedClassHasMethod("Droped", swigMethodTypes1)) EffekseerNativePINVOKE.GUIManagerCallback_DropedSwigExplicitGUIManagerCallback(swigCPtr); else EffekseerNativePINVOKE.GUIManagerCallback_Droped(swigCPtr);
  }

  public virtual void Focused() {
    if (SwigDerivedClassHasMethod("Focused", swigMethodTypes2)) EffekseerNativePINVOKE.GUIManagerCallback_FocusedSwigExplicitGUIManagerCallback(swigCPtr); else EffekseerNativePINVOKE.GUIManagerCallback_Focused(swigCPtr);
  }

  public virtual bool Closing() {
    bool ret = (SwigDerivedClassHasMethod("Closing", swigMethodTypes3) ? EffekseerNativePINVOKE.GUIManagerCallback_ClosingSwigExplicitGUIManagerCallback(swigCPtr) : EffekseerNativePINVOKE.GUIManagerCallback_Closing(swigCPtr));
    return ret;
  }

  public string GetPath() {
    string ret = System.Runtime.InteropServices.Marshal.PtrToStringUni(EffekseerNativePINVOKE.GUIManagerCallback_GetPath(swigCPtr));
    return ret;
  }

  public void SetPath(string path) {
    EffekseerNativePINVOKE.GUIManagerCallback_SetPath(swigCPtr, path);
  }

  private void SwigDirectorConnect() {
    if (SwigDerivedClassHasMethod("Resized", swigMethodTypes0))
      swigDelegate0 = new SwigDelegateGUIManagerCallback_0(SwigDirectorResized);
    if (SwigDerivedClassHasMethod("Droped", swigMethodTypes1))
      swigDelegate1 = new SwigDelegateGUIManagerCallback_1(SwigDirectorDroped);
    if (SwigDerivedClassHasMethod("Focused", swigMethodTypes2))
      swigDelegate2 = new SwigDelegateGUIManagerCallback_2(SwigDirectorFocused);
    if (SwigDerivedClassHasMethod("Closing", swigMethodTypes3))
      swigDelegate3 = new SwigDelegateGUIManagerCallback_3(SwigDirectorClosing);
    EffekseerNativePINVOKE.GUIManagerCallback_director_connect(swigCPtr, swigDelegate0, swigDelegate1, swigDelegate2, swigDelegate3);
  }

  private bool SwigDerivedClassHasMethod(string methodName, global::System.Type[] methodTypes) {
    global::System.Reflection.MethodInfo methodInfo = this.GetType().GetMethod(methodName, global::System.Reflection.BindingFlags.Public | global::System.Reflection.BindingFlags.NonPublic | global::System.Reflection.BindingFlags.Instance, null, methodTypes, null);
    bool hasDerivedMethod = methodInfo.DeclaringType.IsSubclassOf(typeof(GUIManagerCallback));
    return hasDerivedMethod;
  }

  private void SwigDirectorResized(int x, int y) {
    Resized(x, y);
  }

  private void SwigDirectorDroped() {
    Droped();
  }

  private void SwigDirectorFocused() {
    Focused();
  }

  private bool SwigDirectorClosing() {
    return Closing();
  }

  public delegate void SwigDelegateGUIManagerCallback_0(int x, int y);
  public delegate void SwigDelegateGUIManagerCallback_1();
  public delegate void SwigDelegateGUIManagerCallback_2();
  public delegate bool SwigDelegateGUIManagerCallback_3();

  private SwigDelegateGUIManagerCallback_0 swigDelegate0;
  private SwigDelegateGUIManagerCallback_1 swigDelegate1;
  private SwigDelegateGUIManagerCallback_2 swigDelegate2;
  private SwigDelegateGUIManagerCallback_3 swigDelegate3;

  private static global::System.Type[] swigMethodTypes0 = new global::System.Type[] { typeof(int), typeof(int) };
  private static global::System.Type[] swigMethodTypes1 = new global::System.Type[] {  };
  private static global::System.Type[] swigMethodTypes2 = new global::System.Type[] {  };
  private static global::System.Type[] swigMethodTypes3 = new global::System.Type[] {  };
}

}
#ifndef vclass_header
#define vclass_header "0.0.1"

#define class_iden(class_name) CLASS_##class_name
#define class_class(class_name) struct class_iden(class_name)

#define class_construct(class_name, ...) ;}; class_class(class_name) class_iden(class_name) (class_class(class_name) * this __VA_OPT__(,) __VA_ARGS__)
#define class_decl_static(class_name, return_type, function_name, ...) ;}; return_type class_name##_##function_name (class_class(class_name) * this __VA_OPT__(,) __VA_ARGS__) 

#define class_now { if (1)
#define class_later ; struct { char _

#define class_object(class_name, object_name, ...) class_class(class_name) object_name; class_iden(class_name) (&object_name __VA_OPT__(,) __VA_ARGS__)

#define class_call_static(class_name, object_name, function_name, ...) class_name##_##function_name(&object_name __VA_OPT__(,) __VA_ARGS__)

#ifdef class_no_prefix
#define class_no_prefix

#define class class_class

#define construct class_construct
#define function class_decl_static
#define decl class_decl_static

#define now class_now
#define later class_later

#define object class_object
#define call class_call_static

#endif

#ifdef class_v_prefix
#define class_v_prefix

#define vclass class_class

#define vconstr class_construct
#define vfunc class_decl_static

#define vnow class_now
#define vlater class_later

#define vobject class_object
#define vcall class_call_static

#endif

#endif


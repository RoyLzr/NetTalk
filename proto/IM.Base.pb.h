// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: IM.Base.proto

#ifndef PROTOBUF_IM_2eBase_2eproto__INCLUDED
#define PROTOBUF_IM_2eBase_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3000000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace IM {
namespace Base {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_IM_2eBase_2eproto();
void protobuf_AssignDesc_IM_2eBase_2eproto();
void protobuf_ShutdownFile_IM_2eBase_2eproto();

class UserInfo;

enum RegisterCmdID {
  NONEREG = 0,
  CID_REGISTER_REQ = 1025,
  CID_REGISTER_RES = 1026,
  RegisterCmdID_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  RegisterCmdID_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool RegisterCmdID_IsValid(int value);
const RegisterCmdID RegisterCmdID_MIN = NONEREG;
const RegisterCmdID RegisterCmdID_MAX = CID_REGISTER_RES;
const int RegisterCmdID_ARRAYSIZE = RegisterCmdID_MAX + 1;

const ::google::protobuf::EnumDescriptor* RegisterCmdID_descriptor();
inline const ::std::string& RegisterCmdID_Name(RegisterCmdID value) {
  return ::google::protobuf::internal::NameOfEnum(
    RegisterCmdID_descriptor(), value);
}
inline bool RegisterCmdID_Parse(
    const ::std::string& name, RegisterCmdID* value) {
  return ::google::protobuf::internal::ParseNamedEnum<RegisterCmdID>(
    RegisterCmdID_descriptor(), name, value);
}
enum LoginCmdID {
  NONELOG = 0,
  CID_LOGIN_REQ_USERLOGIN = 257,
  CID_LOGIN_RES_USERLOGIN = 258,
  CID_LOGIN_REQ_USERLOGOUT = 259,
  CID_LOGIN_RES_USERLOGOUT = 260,
  LoginCmdID_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  LoginCmdID_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool LoginCmdID_IsValid(int value);
const LoginCmdID LoginCmdID_MIN = NONELOG;
const LoginCmdID LoginCmdID_MAX = CID_LOGIN_RES_USERLOGOUT;
const int LoginCmdID_ARRAYSIZE = LoginCmdID_MAX + 1;

const ::google::protobuf::EnumDescriptor* LoginCmdID_descriptor();
inline const ::std::string& LoginCmdID_Name(LoginCmdID value) {
  return ::google::protobuf::internal::NameOfEnum(
    LoginCmdID_descriptor(), value);
}
inline bool LoginCmdID_Parse(
    const ::std::string& name, LoginCmdID* value) {
  return ::google::protobuf::internal::ParseNamedEnum<LoginCmdID>(
    LoginCmdID_descriptor(), name, value);
}
enum BuddyCmdID {
  NONEBUDDY = 0,
  CID_BUDDY_REQ_USER_LIST = 513,
  CID_BUDDY_RES_USER_LIST = 514,
  CID_BUDDY_REQ_BUILD_USER = 515,
  CID_BUDDY_RES_BUILD_USER = 516,
  CID_BUDDY_REQ_DEL_USER = 517,
  CID_BUDDY_RES_DEL_USER = 518,
  BuddyCmdID_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  BuddyCmdID_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool BuddyCmdID_IsValid(int value);
const BuddyCmdID BuddyCmdID_MIN = NONEBUDDY;
const BuddyCmdID BuddyCmdID_MAX = CID_BUDDY_RES_DEL_USER;
const int BuddyCmdID_ARRAYSIZE = BuddyCmdID_MAX + 1;

const ::google::protobuf::EnumDescriptor* BuddyCmdID_descriptor();
inline const ::std::string& BuddyCmdID_Name(BuddyCmdID value) {
  return ::google::protobuf::internal::NameOfEnum(
    BuddyCmdID_descriptor(), value);
}
inline bool BuddyCmdID_Parse(
    const ::std::string& name, BuddyCmdID* value) {
  return ::google::protobuf::internal::ParseNamedEnum<BuddyCmdID>(
    BuddyCmdID_descriptor(), name, value);
}
enum SessionCmdID {
  NONESESS = 0,
  CID_SESSION_REQ_BUILD = 769,
  CID_SESSION_RES_BUILD = 770,
  CID_SESSION_REQ_STOP = 771,
  CID_SESSION_RES_STOP = 772,
  SessionCmdID_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  SessionCmdID_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool SessionCmdID_IsValid(int value);
const SessionCmdID SessionCmdID_MIN = NONESESS;
const SessionCmdID SessionCmdID_MAX = CID_SESSION_RES_STOP;
const int SessionCmdID_ARRAYSIZE = SessionCmdID_MAX + 1;

const ::google::protobuf::EnumDescriptor* SessionCmdID_descriptor();
inline const ::std::string& SessionCmdID_Name(SessionCmdID value) {
  return ::google::protobuf::internal::NameOfEnum(
    SessionCmdID_descriptor(), value);
}
inline bool SessionCmdID_Parse(
    const ::std::string& name, SessionCmdID* value) {
  return ::google::protobuf::internal::ParseNamedEnum<SessionCmdID>(
    SessionCmdID_descriptor(), name, value);
}
enum ResultType {
  RESULT_LOGIN_SUCC = 0,
  RESULT_LOGIN_FAIL = 1,
  RESULT_BUDDY_SUCC = 2,
  RESULT_BUDDY_FAIL = 3,
  RESULT_SESSION_SUCC = 4,
  RESULT_SESSION_FAIL = 5,
  RESULT_REGISTER_SUCC = 6,
  RESULT_REGISTER_FAIL = 7,
  ResultType_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  ResultType_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool ResultType_IsValid(int value);
const ResultType ResultType_MIN = RESULT_LOGIN_SUCC;
const ResultType ResultType_MAX = RESULT_REGISTER_FAIL;
const int ResultType_ARRAYSIZE = ResultType_MAX + 1;

const ::google::protobuf::EnumDescriptor* ResultType_descriptor();
inline const ::std::string& ResultType_Name(ResultType value) {
  return ::google::protobuf::internal::NameOfEnum(
    ResultType_descriptor(), value);
}
inline bool ResultType_Parse(
    const ::std::string& name, ResultType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<ResultType>(
    ResultType_descriptor(), name, value);
}
// ===================================================================

class UserInfo : public ::google::protobuf::Message {
 public:
  UserInfo();
  virtual ~UserInfo();

  UserInfo(const UserInfo& from);

  inline UserInfo& operator=(const UserInfo& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const UserInfo& default_instance();

  void Swap(UserInfo* other);

  // implements Message ----------------------------------------------

  inline UserInfo* New() const { return New(NULL); }

  UserInfo* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const UserInfo& from);
  void MergeFrom(const UserInfo& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(UserInfo* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional uint32 user_id = 1;
  void clear_user_id();
  static const int kUserIdFieldNumber = 1;
  ::google::protobuf::uint32 user_id() const;
  void set_user_id(::google::protobuf::uint32 value);

  // optional string user_name = 2;
  void clear_user_name();
  static const int kUserNameFieldNumber = 2;
  const ::std::string& user_name() const;
  void set_user_name(const ::std::string& value);
  void set_user_name(const char* value);
  void set_user_name(const char* value, size_t size);
  ::std::string* mutable_user_name();
  ::std::string* release_user_name();
  void set_allocated_user_name(::std::string* user_name);

  // optional uint32 created = 3;
  void clear_created();
  static const int kCreatedFieldNumber = 3;
  ::google::protobuf::uint32 created() const;
  void set_created(::google::protobuf::uint32 value);

  // optional uint32 user_lastlog = 4;
  void clear_user_lastlog();
  static const int kUserLastlogFieldNumber = 4;
  ::google::protobuf::uint32 user_lastlog() const;
  void set_user_lastlog(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:IM.Base.UserInfo)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::google::protobuf::internal::ArenaStringPtr user_name_;
  ::google::protobuf::uint32 user_id_;
  ::google::protobuf::uint32 created_;
  ::google::protobuf::uint32 user_lastlog_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_IM_2eBase_2eproto();
  friend void protobuf_AssignDesc_IM_2eBase_2eproto();
  friend void protobuf_ShutdownFile_IM_2eBase_2eproto();

  void InitAsDefaultInstance();
  static UserInfo* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// UserInfo

// optional uint32 user_id = 1;
inline void UserInfo::clear_user_id() {
  user_id_ = 0u;
}
inline ::google::protobuf::uint32 UserInfo::user_id() const {
  // @@protoc_insertion_point(field_get:IM.Base.UserInfo.user_id)
  return user_id_;
}
inline void UserInfo::set_user_id(::google::protobuf::uint32 value) {
  
  user_id_ = value;
  // @@protoc_insertion_point(field_set:IM.Base.UserInfo.user_id)
}

// optional string user_name = 2;
inline void UserInfo::clear_user_name() {
  user_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& UserInfo::user_name() const {
  // @@protoc_insertion_point(field_get:IM.Base.UserInfo.user_name)
  return user_name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void UserInfo::set_user_name(const ::std::string& value) {
  
  user_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:IM.Base.UserInfo.user_name)
}
inline void UserInfo::set_user_name(const char* value) {
  
  user_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:IM.Base.UserInfo.user_name)
}
inline void UserInfo::set_user_name(const char* value, size_t size) {
  
  user_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:IM.Base.UserInfo.user_name)
}
inline ::std::string* UserInfo::mutable_user_name() {
  
  // @@protoc_insertion_point(field_mutable:IM.Base.UserInfo.user_name)
  return user_name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* UserInfo::release_user_name() {
  // @@protoc_insertion_point(field_release:IM.Base.UserInfo.user_name)
  
  return user_name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void UserInfo::set_allocated_user_name(::std::string* user_name) {
  if (user_name != NULL) {
    
  } else {
    
  }
  user_name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), user_name);
  // @@protoc_insertion_point(field_set_allocated:IM.Base.UserInfo.user_name)
}

// optional uint32 created = 3;
inline void UserInfo::clear_created() {
  created_ = 0u;
}
inline ::google::protobuf::uint32 UserInfo::created() const {
  // @@protoc_insertion_point(field_get:IM.Base.UserInfo.created)
  return created_;
}
inline void UserInfo::set_created(::google::protobuf::uint32 value) {
  
  created_ = value;
  // @@protoc_insertion_point(field_set:IM.Base.UserInfo.created)
}

// optional uint32 user_lastlog = 4;
inline void UserInfo::clear_user_lastlog() {
  user_lastlog_ = 0u;
}
inline ::google::protobuf::uint32 UserInfo::user_lastlog() const {
  // @@protoc_insertion_point(field_get:IM.Base.UserInfo.user_lastlog)
  return user_lastlog_;
}
inline void UserInfo::set_user_lastlog(::google::protobuf::uint32 value) {
  
  user_lastlog_ = value;
  // @@protoc_insertion_point(field_set:IM.Base.UserInfo.user_lastlog)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace Base
}  // namespace IM

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::IM::Base::RegisterCmdID> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::IM::Base::RegisterCmdID>() {
  return ::IM::Base::RegisterCmdID_descriptor();
}
template <> struct is_proto_enum< ::IM::Base::LoginCmdID> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::IM::Base::LoginCmdID>() {
  return ::IM::Base::LoginCmdID_descriptor();
}
template <> struct is_proto_enum< ::IM::Base::BuddyCmdID> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::IM::Base::BuddyCmdID>() {
  return ::IM::Base::BuddyCmdID_descriptor();
}
template <> struct is_proto_enum< ::IM::Base::SessionCmdID> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::IM::Base::SessionCmdID>() {
  return ::IM::Base::SessionCmdID_descriptor();
}
template <> struct is_proto_enum< ::IM::Base::ResultType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::IM::Base::ResultType>() {
  return ::IM::Base::ResultType_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_IM_2eBase_2eproto__INCLUDED
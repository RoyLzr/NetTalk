// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: IM.Log.proto

#ifndef PROTOBUF_IM_2eLog_2eproto__INCLUDED
#define PROTOBUF_IM_2eLog_2eproto__INCLUDED

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
#include <google/protobuf/unknown_field_set.h>
#include "IM.Base.pb.h"
// @@protoc_insertion_point(includes)

namespace IM {
namespace Log {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_IM_2eLog_2eproto();
void protobuf_AssignDesc_IM_2eLog_2eproto();
void protobuf_ShutdownFile_IM_2eLog_2eproto();

class IMLogInReq;
class IMLogRes;

// ===================================================================

class IMLogInReq : public ::google::protobuf::Message {
 public:
  IMLogInReq();
  virtual ~IMLogInReq();

  IMLogInReq(const IMLogInReq& from);

  inline IMLogInReq& operator=(const IMLogInReq& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const IMLogInReq& default_instance();

  void Swap(IMLogInReq* other);

  // implements Message ----------------------------------------------

  inline IMLogInReq* New() const { return New(NULL); }

  IMLogInReq* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const IMLogInReq& from);
  void MergeFrom(const IMLogInReq& from);
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
  void InternalSwap(IMLogInReq* other);
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

  // optional string name = 1;
  void clear_name();
  static const int kNameFieldNumber = 1;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // optional string password = 2;
  void clear_password();
  static const int kPasswordFieldNumber = 2;
  const ::std::string& password() const;
  void set_password(const ::std::string& value);
  void set_password(const char* value);
  void set_password(const char* value, size_t size);
  ::std::string* mutable_password();
  ::std::string* release_password();
  void set_allocated_password(::std::string* password);

  // @@protoc_insertion_point(class_scope:IM.Log.IMLogInReq)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  ::google::protobuf::internal::ArenaStringPtr password_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_IM_2eLog_2eproto();
  friend void protobuf_AssignDesc_IM_2eLog_2eproto();
  friend void protobuf_ShutdownFile_IM_2eLog_2eproto();

  void InitAsDefaultInstance();
  static IMLogInReq* default_instance_;
};
// -------------------------------------------------------------------

class IMLogRes : public ::google::protobuf::Message {
 public:
  IMLogRes();
  virtual ~IMLogRes();

  IMLogRes(const IMLogRes& from);

  inline IMLogRes& operator=(const IMLogRes& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const IMLogRes& default_instance();

  void Swap(IMLogRes* other);

  // implements Message ----------------------------------------------

  inline IMLogRes* New() const { return New(NULL); }

  IMLogRes* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const IMLogRes& from);
  void MergeFrom(const IMLogRes& from);
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
  void InternalSwap(IMLogRes* other);
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

  // optional .IM.Base.ResultType logRes = 1;
  void clear_logres();
  static const int kLogResFieldNumber = 1;
  ::IM::Base::ResultType logres() const;
  void set_logres(::IM::Base::ResultType value);

  // repeated .IM.Base.UserInfo friend = 2;
  int friend__size() const;
  void clear_friend_();
  static const int kFriendFieldNumber = 2;
  const ::IM::Base::UserInfo& friend_(int index) const;
  ::IM::Base::UserInfo* mutable_friend_(int index);
  ::IM::Base::UserInfo* add_friend_();
  ::google::protobuf::RepeatedPtrField< ::IM::Base::UserInfo >*
      mutable_friend_();
  const ::google::protobuf::RepeatedPtrField< ::IM::Base::UserInfo >&
      friend_() const;

  // @@protoc_insertion_point(class_scope:IM.Log.IMLogRes)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::google::protobuf::RepeatedPtrField< ::IM::Base::UserInfo > friend__;
  int logres_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_IM_2eLog_2eproto();
  friend void protobuf_AssignDesc_IM_2eLog_2eproto();
  friend void protobuf_ShutdownFile_IM_2eLog_2eproto();

  void InitAsDefaultInstance();
  static IMLogRes* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// IMLogInReq

// optional string name = 1;
inline void IMLogInReq::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& IMLogInReq::name() const {
  // @@protoc_insertion_point(field_get:IM.Log.IMLogInReq.name)
  return name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void IMLogInReq::set_name(const ::std::string& value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:IM.Log.IMLogInReq.name)
}
inline void IMLogInReq::set_name(const char* value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:IM.Log.IMLogInReq.name)
}
inline void IMLogInReq::set_name(const char* value, size_t size) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:IM.Log.IMLogInReq.name)
}
inline ::std::string* IMLogInReq::mutable_name() {
  
  // @@protoc_insertion_point(field_mutable:IM.Log.IMLogInReq.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* IMLogInReq::release_name() {
  // @@protoc_insertion_point(field_release:IM.Log.IMLogInReq.name)
  
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void IMLogInReq::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    
  } else {
    
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:IM.Log.IMLogInReq.name)
}

// optional string password = 2;
inline void IMLogInReq::clear_password() {
  password_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& IMLogInReq::password() const {
  // @@protoc_insertion_point(field_get:IM.Log.IMLogInReq.password)
  return password_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void IMLogInReq::set_password(const ::std::string& value) {
  
  password_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:IM.Log.IMLogInReq.password)
}
inline void IMLogInReq::set_password(const char* value) {
  
  password_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:IM.Log.IMLogInReq.password)
}
inline void IMLogInReq::set_password(const char* value, size_t size) {
  
  password_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:IM.Log.IMLogInReq.password)
}
inline ::std::string* IMLogInReq::mutable_password() {
  
  // @@protoc_insertion_point(field_mutable:IM.Log.IMLogInReq.password)
  return password_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* IMLogInReq::release_password() {
  // @@protoc_insertion_point(field_release:IM.Log.IMLogInReq.password)
  
  return password_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void IMLogInReq::set_allocated_password(::std::string* password) {
  if (password != NULL) {
    
  } else {
    
  }
  password_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), password);
  // @@protoc_insertion_point(field_set_allocated:IM.Log.IMLogInReq.password)
}

// -------------------------------------------------------------------

// IMLogRes

// optional .IM.Base.ResultType logRes = 1;
inline void IMLogRes::clear_logres() {
  logres_ = 0;
}
inline ::IM::Base::ResultType IMLogRes::logres() const {
  // @@protoc_insertion_point(field_get:IM.Log.IMLogRes.logRes)
  return static_cast< ::IM::Base::ResultType >(logres_);
}
inline void IMLogRes::set_logres(::IM::Base::ResultType value) {
  
  logres_ = value;
  // @@protoc_insertion_point(field_set:IM.Log.IMLogRes.logRes)
}

// repeated .IM.Base.UserInfo friend = 2;
inline int IMLogRes::friend__size() const {
  return friend__.size();
}
inline void IMLogRes::clear_friend_() {
  friend__.Clear();
}
inline const ::IM::Base::UserInfo& IMLogRes::friend_(int index) const {
  // @@protoc_insertion_point(field_get:IM.Log.IMLogRes.friend)
  return friend__.Get(index);
}
inline ::IM::Base::UserInfo* IMLogRes::mutable_friend_(int index) {
  // @@protoc_insertion_point(field_mutable:IM.Log.IMLogRes.friend)
  return friend__.Mutable(index);
}
inline ::IM::Base::UserInfo* IMLogRes::add_friend_() {
  // @@protoc_insertion_point(field_add:IM.Log.IMLogRes.friend)
  return friend__.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::IM::Base::UserInfo >*
IMLogRes::mutable_friend_() {
  // @@protoc_insertion_point(field_mutable_list:IM.Log.IMLogRes.friend)
  return &friend__;
}
inline const ::google::protobuf::RepeatedPtrField< ::IM::Base::UserInfo >&
IMLogRes::friend_() const {
  // @@protoc_insertion_point(field_list:IM.Log.IMLogRes.friend)
  return friend__;
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace Log
}  // namespace IM

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_IM_2eLog_2eproto__INCLUDED

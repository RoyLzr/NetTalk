// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: IM.Register.proto

#ifndef PROTOBUF_IM_2eRegister_2eproto__INCLUDED
#define PROTOBUF_IM_2eRegister_2eproto__INCLUDED

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
namespace Register {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_IM_2eRegister_2eproto();
void protobuf_AssignDesc_IM_2eRegister_2eproto();
void protobuf_ShutdownFile_IM_2eRegister_2eproto();

class IMRegisterReq;
class IMRegisterRes;

// ===================================================================

class IMRegisterReq : public ::google::protobuf::Message {
 public:
  IMRegisterReq();
  virtual ~IMRegisterReq();

  IMRegisterReq(const IMRegisterReq& from);

  inline IMRegisterReq& operator=(const IMRegisterReq& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const IMRegisterReq& default_instance();

  void Swap(IMRegisterReq* other);

  // implements Message ----------------------------------------------

  inline IMRegisterReq* New() const { return New(NULL); }

  IMRegisterReq* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const IMRegisterReq& from);
  void MergeFrom(const IMRegisterReq& from);
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
  void InternalSwap(IMRegisterReq* other);
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

  // optional uint32 created = 3;
  void clear_created();
  static const int kCreatedFieldNumber = 3;
  ::google::protobuf::uint32 created() const;
  void set_created(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:IM.Register.IMRegisterReq)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  ::google::protobuf::internal::ArenaStringPtr password_;
  ::google::protobuf::uint32 created_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_IM_2eRegister_2eproto();
  friend void protobuf_AssignDesc_IM_2eRegister_2eproto();
  friend void protobuf_ShutdownFile_IM_2eRegister_2eproto();

  void InitAsDefaultInstance();
  static IMRegisterReq* default_instance_;
};
// -------------------------------------------------------------------

class IMRegisterRes : public ::google::protobuf::Message {
 public:
  IMRegisterRes();
  virtual ~IMRegisterRes();

  IMRegisterRes(const IMRegisterRes& from);

  inline IMRegisterRes& operator=(const IMRegisterRes& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const IMRegisterRes& default_instance();

  void Swap(IMRegisterRes* other);

  // implements Message ----------------------------------------------

  inline IMRegisterRes* New() const { return New(NULL); }

  IMRegisterRes* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const IMRegisterRes& from);
  void MergeFrom(const IMRegisterRes& from);
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
  void InternalSwap(IMRegisterRes* other);
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

  // optional .IM.Base.ResultType status = 1;
  void clear_status();
  static const int kStatusFieldNumber = 1;
  ::IM::Base::ResultType status() const;
  void set_status(::IM::Base::ResultType value);

  // optional string reason = 2;
  void clear_reason();
  static const int kReasonFieldNumber = 2;
  const ::std::string& reason() const;
  void set_reason(const ::std::string& value);
  void set_reason(const char* value);
  void set_reason(const char* value, size_t size);
  ::std::string* mutable_reason();
  ::std::string* release_reason();
  void set_allocated_reason(::std::string* reason);

  // optional uint32 created = 3;
  void clear_created();
  static const int kCreatedFieldNumber = 3;
  ::google::protobuf::uint32 created() const;
  void set_created(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:IM.Register.IMRegisterRes)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::google::protobuf::internal::ArenaStringPtr reason_;
  int status_;
  ::google::protobuf::uint32 created_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_IM_2eRegister_2eproto();
  friend void protobuf_AssignDesc_IM_2eRegister_2eproto();
  friend void protobuf_ShutdownFile_IM_2eRegister_2eproto();

  void InitAsDefaultInstance();
  static IMRegisterRes* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// IMRegisterReq

// optional string name = 1;
inline void IMRegisterReq::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& IMRegisterReq::name() const {
  // @@protoc_insertion_point(field_get:IM.Register.IMRegisterReq.name)
  return name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void IMRegisterReq::set_name(const ::std::string& value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:IM.Register.IMRegisterReq.name)
}
inline void IMRegisterReq::set_name(const char* value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:IM.Register.IMRegisterReq.name)
}
inline void IMRegisterReq::set_name(const char* value, size_t size) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:IM.Register.IMRegisterReq.name)
}
inline ::std::string* IMRegisterReq::mutable_name() {
  
  // @@protoc_insertion_point(field_mutable:IM.Register.IMRegisterReq.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* IMRegisterReq::release_name() {
  // @@protoc_insertion_point(field_release:IM.Register.IMRegisterReq.name)
  
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void IMRegisterReq::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    
  } else {
    
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:IM.Register.IMRegisterReq.name)
}

// optional string password = 2;
inline void IMRegisterReq::clear_password() {
  password_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& IMRegisterReq::password() const {
  // @@protoc_insertion_point(field_get:IM.Register.IMRegisterReq.password)
  return password_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void IMRegisterReq::set_password(const ::std::string& value) {
  
  password_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:IM.Register.IMRegisterReq.password)
}
inline void IMRegisterReq::set_password(const char* value) {
  
  password_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:IM.Register.IMRegisterReq.password)
}
inline void IMRegisterReq::set_password(const char* value, size_t size) {
  
  password_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:IM.Register.IMRegisterReq.password)
}
inline ::std::string* IMRegisterReq::mutable_password() {
  
  // @@protoc_insertion_point(field_mutable:IM.Register.IMRegisterReq.password)
  return password_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* IMRegisterReq::release_password() {
  // @@protoc_insertion_point(field_release:IM.Register.IMRegisterReq.password)
  
  return password_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void IMRegisterReq::set_allocated_password(::std::string* password) {
  if (password != NULL) {
    
  } else {
    
  }
  password_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), password);
  // @@protoc_insertion_point(field_set_allocated:IM.Register.IMRegisterReq.password)
}

// optional uint32 created = 3;
inline void IMRegisterReq::clear_created() {
  created_ = 0u;
}
inline ::google::protobuf::uint32 IMRegisterReq::created() const {
  // @@protoc_insertion_point(field_get:IM.Register.IMRegisterReq.created)
  return created_;
}
inline void IMRegisterReq::set_created(::google::protobuf::uint32 value) {
  
  created_ = value;
  // @@protoc_insertion_point(field_set:IM.Register.IMRegisterReq.created)
}

// -------------------------------------------------------------------

// IMRegisterRes

// optional .IM.Base.ResultType status = 1;
inline void IMRegisterRes::clear_status() {
  status_ = 0;
}
inline ::IM::Base::ResultType IMRegisterRes::status() const {
  // @@protoc_insertion_point(field_get:IM.Register.IMRegisterRes.status)
  return static_cast< ::IM::Base::ResultType >(status_);
}
inline void IMRegisterRes::set_status(::IM::Base::ResultType value) {
  
  status_ = value;
  // @@protoc_insertion_point(field_set:IM.Register.IMRegisterRes.status)
}

// optional string reason = 2;
inline void IMRegisterRes::clear_reason() {
  reason_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& IMRegisterRes::reason() const {
  // @@protoc_insertion_point(field_get:IM.Register.IMRegisterRes.reason)
  return reason_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void IMRegisterRes::set_reason(const ::std::string& value) {
  
  reason_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:IM.Register.IMRegisterRes.reason)
}
inline void IMRegisterRes::set_reason(const char* value) {
  
  reason_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:IM.Register.IMRegisterRes.reason)
}
inline void IMRegisterRes::set_reason(const char* value, size_t size) {
  
  reason_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:IM.Register.IMRegisterRes.reason)
}
inline ::std::string* IMRegisterRes::mutable_reason() {
  
  // @@protoc_insertion_point(field_mutable:IM.Register.IMRegisterRes.reason)
  return reason_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* IMRegisterRes::release_reason() {
  // @@protoc_insertion_point(field_release:IM.Register.IMRegisterRes.reason)
  
  return reason_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void IMRegisterRes::set_allocated_reason(::std::string* reason) {
  if (reason != NULL) {
    
  } else {
    
  }
  reason_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), reason);
  // @@protoc_insertion_point(field_set_allocated:IM.Register.IMRegisterRes.reason)
}

// optional uint32 created = 3;
inline void IMRegisterRes::clear_created() {
  created_ = 0u;
}
inline ::google::protobuf::uint32 IMRegisterRes::created() const {
  // @@protoc_insertion_point(field_get:IM.Register.IMRegisterRes.created)
  return created_;
}
inline void IMRegisterRes::set_created(::google::protobuf::uint32 value) {
  
  created_ = value;
  // @@protoc_insertion_point(field_set:IM.Register.IMRegisterRes.created)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace Register
}  // namespace IM

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_IM_2eRegister_2eproto__INCLUDED
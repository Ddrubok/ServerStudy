
#include "Struct.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace Protocol {
constexpr Player::Player(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : name_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , id_(uint64_t{0u})
  , playertype_(0)
{}
struct PlayerDefaultTypeInternal {
  constexpr PlayerDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~PlayerDefaultTypeInternal() {}
  union {
    Player _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PlayerDefaultTypeInternal _Player_default_instance_;
}  static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_Struct_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_Struct_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_Struct_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_Struct_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,    PROTOBUF_FIELD_OFFSET(::Protocol::Player, _internal_metadata_),
  ~0u,    ~0u,    ~0u,    PROTOBUF_FIELD_OFFSET(::Protocol::Player, id_),
  PROTOBUF_FIELD_OFFSET(::Protocol::Player, name_),
  PROTOBUF_FIELD_OFFSET(::Protocol::Player, playertype_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::Protocol::Player)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::Protocol::_Player_default_instance_),
};

const char descriptor_table_protodef_Struct_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\014Struct.proto\022\010Protocol\032\nEnum.proto\"L\n\006"
  "Player\022\n\n\002id\030\001 \001(\004\022\014\n\004name\030\002 \001(\t\022(\n\nplay"
  "erType\030\003 \001(\0162\024.Protocol.PlayerTypeb\006prot"
  "o3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_Struct_2eproto_deps[1] = {
  &::descriptor_table_Enum_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_Struct_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_Struct_2eproto = {
  false, false, 122, descriptor_table_protodef_Struct_2eproto, "Struct.proto", 
  &descriptor_table_Struct_2eproto_once, descriptor_table_Struct_2eproto_deps, 1, 1,
  schemas, file_default_instances, TableStruct_Struct_2eproto::offsets,
  file_level_metadata_Struct_2eproto, file_level_enum_descriptors_Struct_2eproto, file_level_service_descriptors_Struct_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_Struct_2eproto_getter() {
  return &descriptor_table_Struct_2eproto;
}

PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_Struct_2eproto(&descriptor_table_Struct_2eproto);
namespace Protocol {


class Player::_Internal {
 public:
};

Player::Player(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  }
Player::Player(const Player& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_name().empty()) {
    name_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_name(), 
      GetArenaForAllocation());
  }
  ::memcpy(&id_, &from.id_,
    static_cast<size_t>(reinterpret_cast<char*>(&playertype_) -
    reinterpret_cast<char*>(&id_)) + sizeof(playertype_));
  }

void Player::SharedCtor() {
name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&id_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&playertype_) -
    reinterpret_cast<char*>(&id_)) + sizeof(playertype_));
}

Player::~Player() {
    SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void Player::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  name_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void Player::ArenaDtor(void* object) {
  Player* _this = reinterpret_cast< Player* >(object);
  (void)_this;
}
void Player::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Player::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Player::Clear() {
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
    (void) cached_has_bits;

  name_.ClearToEmpty();
  ::memset(&id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&playertype_) -
      reinterpret_cast<char*>(&id_)) + sizeof(playertype_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Player::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
            case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
            case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          auto str = _internal_mutable_name();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "Protocol.Player.name"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
            case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_playertype(static_cast<::Protocol::PlayerType>(val));
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }    }  success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* Player::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
    ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

    if (this->id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt64ToArray(1, this->_internal_id(), target);
  }

    if (!this->name().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_name().data(), static_cast<int>(this->_internal_name().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "Protocol.Player.name");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_name(), target);
  }

    if (this->playertype() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      3, this->_internal_playertype(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
    return target;
}

size_t Player::ByteSizeLong() const {
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
    (void) cached_has_bits;

    if (!this->name().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_name());
  }

    if (this->id() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt64Size(
        this->_internal_id());
  }

    if (this->playertype() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_playertype());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void Player::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  GOOGLE_DCHECK_NE(&from, this);
  const Player* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<Player>(
          &from);
  if (source == nullptr) {
      ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
      MergeFrom(*source);
  }
}

void Player::MergeFrom(const Player& from) {
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from.name().empty()) {
    _internal_set_name(from._internal_name());
  }
  if (from.id() != 0) {
    _internal_set_id(from._internal_id());
  }
  if (from.playertype() != 0) {
    _internal_set_playertype(from._internal_playertype());
  }
}

void Player::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Player::CopyFrom(const Player& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Player::IsInitialized() const {
  return true;
}

void Player::InternalSwap(Player* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &name_, GetArenaForAllocation(),
      &other->name_, other->GetArenaForAllocation()
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(Player, playertype_)
      + sizeof(Player::playertype_)
      - PROTOBUF_FIELD_OFFSET(Player, id_)>(
          reinterpret_cast<char*>(&id_),
          reinterpret_cast<char*>(&other->id_));
}

::PROTOBUF_NAMESPACE_ID::Metadata Player::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_Struct_2eproto_getter, &descriptor_table_Struct_2eproto_once,
      file_level_metadata_Struct_2eproto[0]);
}

}  PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::Protocol::Player* Arena::CreateMaybeMessage< ::Protocol::Player >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Protocol::Player >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

#include <google/protobuf/port_undef.inc>

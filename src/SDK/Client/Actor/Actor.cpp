#include "Actor.hpp"
#include "../../../Utils/Memory/Game/SignatureAndOffsetManager.hpp"

// TODO add comments to all components, replace their sigs with simpler ones ?

template<typename Component>
Component *Actor::tryGet(uintptr_t addr) { // TODO: Multiversion
    auto ctx = GetEntityContext();

    using efunc = Component *(__thiscall *)(uintptr_t *, const EntityId &);
    auto func = reinterpret_cast<efunc>(addr);
    return func(&ctx->basicReg, ctx->id);
}

bool Actor::isAlive() {
    static int off = GET_OFFSET("Actor::isPlayer");
    return Memory::CallVFuncI<bool>(off, this);
}

std::string *Actor::getXuid(std::string *str) {
    static int off = GET_OFFSET("Actor::getXuid");
    return Memory::CallVFuncI<std::string *, std::string *>(off, this, str);
}

ActorTypeComponent *Actor::getActorTypeComponent() {
    static uintptr_t sig;

    if (sig == NULL) {
        sig = Memory::findSig(GET_SIG("Actor::getActorTypeComponent"));
    }

    return tryGet<ActorTypeComponent>(sig);
}


int Actor::getEntityTypeId() {
    return getActorTypeComponent()->type;
}

bool Actor::canSee(const Actor& actor) {
    using canSeeFunc = bool (__fastcall *)(Actor *, const Actor&);
    static auto canSee = reinterpret_cast<canSeeFunc>(Memory::offsetFromSig(
            Memory::findSig(GET_SIG("Actor::canSee")), 1));
    return canSee(this, actor);

    //return Memory::CallVFunc<82, bool, Player const&>(this, actor);
}

MobEffectInstance *Actor::getEffect(MobEffect *effect) {
    static uintptr_t addr = Memory::findSig(GET_SIG("Actor::getEffect"));
    static auto realAddr = addr + 1 + 4 + *reinterpret_cast<int *>(addr + 1);
    auto fn = reinterpret_cast<MobEffectInstance *(__cdecl *)(Actor *, MobEffect *)>(realAddr);
    return fn(this, effect);
}

bool Actor::getActorFlag(int flag) {
    static int off = GET_OFFSET("Actor::getActorFlag");
    return Memory::CallVFuncI<bool, int>(off, this, flag);
}

Vec3<float> *Actor::getPosition() {
    return &this->stateVector->Pos;
}

ItemStack *Actor::getArmor(int slot) {
    static uintptr_t sig;

    if (sig == NULL) {
        sig = Memory::findSig(GET_SIG("Actor::getArmor"));
    }

    auto fn = reinterpret_cast<ItemStack *(__thiscall *)(Actor *, int)>(sig);
    return fn(this, slot);
}

MoveInputComponent *Actor::getMoveInputHandler() { //??$try_get@UMoveInputComponent

    static uintptr_t sig;

    if (sig == NULL) {
        sig = Memory::findSig(GET_SIG("Actor::getMoveInputHandler"));
    }

    return tryGet<MoveInputComponent>(sig);

}

ActorHeadRotationComponent *Actor::getActorHeadRotationComponent() { //??$try_get@UActorHeadRotationComponent

    static uintptr_t sig;

    if (sig == NULL) {
        sig = Memory::findSig(GET_SIG("Actor::getActorHeadRotationComponent"));
    }

    return tryGet<ActorHeadRotationComponent>(sig);

}

ItemStack *Actor::getOffhandSlot() {
    static uintptr_t sig;

    if (sig == NULL) {
        sig = Memory::findSig(GET_SIG("Actor::getOffhandSlot"));
    }

    auto fn = reinterpret_cast<ItemStack *(__thiscall *)(Actor *)>(sig);
    return fn(this);
}

EntityContext *Actor::GetEntityContext() { // TODO: Multiversion
    auto address = reinterpret_cast<uintptr_t>(this);
    if(WinrtUtils::check(20, 50)) {
        return reinterpret_cast<EntityContext *>(reinterpret_cast<V1_20_50::EntityContext *>(address + 8));
    } else {
        return reinterpret_cast<EntityContext *>(reinterpret_cast<V1_20_40::EntityContext *>(address + 8));
    }
}

void Actor::setNametag(std::string *name) {
    static uintptr_t sig;

    if (sig == NULL) {
        sig = Memory::findSig(GET_SIG("Actor::setNametag"));
    }

    auto fn = reinterpret_cast<void (__thiscall *)(Actor *, std::string *)>(sig);
    return fn(this, name);
}

/*
std::uint64_t Actor::getRuntimeID() {
    static uintptr_t sig;

    if (sig == NULL) {
        sig = Memory::findSig("40 53 48 83 EC 20 8B 41 18 48 8B DA 48 8B 49 10 48 8D 54 24 30 89 44 24 30 E8 ?? ?? ?? ?? 48 85 C0 74 0F");
    }

    auto fn = reinterpret_cast<std::uint64_t (__thiscall*)(Actor*)>(sig);
    return fn(this);
}
*/

std::string *Actor::getNametag() {
    static uintptr_t sig;

    if (sig == NULL) {
        sig = Memory::findSig(GET_SIG("Actor::getNametag"));
    }

    auto fn = reinterpret_cast<std::string *(__thiscall *)(Actor *)>(sig);
    return fn(this);
}

bool Actor::isPlayer() {
    static int off = GET_OFFSET("Actor::isPlayer");
    return Memory::CallVFuncI<bool>(off, this);
}

bool Actor::hasCategory(ActorCategory category) {
    return ((int) this->categories & (int) category) != 0;
}

RenderPositionComponent *Actor::getRenderPositionComponent() { //??$try_get@URenderPositionComponent
    static uintptr_t sig;

    if (sig == NULL) {
        sig = Memory::findSig(GET_SIG("Actor::getRenderPositionComponent"));
    }

    return tryGet<RenderPositionComponent>(sig);
}

bool Actor::isValidTarget(Actor *actor) {
    static int off = GET_OFFSET("Actor::isValidTarget");
    return Memory::CallVFuncI<bool, Actor *>(off, this, actor);
}

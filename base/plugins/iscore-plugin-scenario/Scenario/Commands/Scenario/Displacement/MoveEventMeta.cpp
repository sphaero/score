#include "MoveEventMeta.hpp"
#include <Scenario/Commands/Scenario/Displacement/MoveEventList.hpp>
#include "MoveEventFactoryInterface.hpp"

MoveEventMeta::MoveEventMeta(
        Path<ScenarioModel>&& scenarioPath,
        const Id<EventModel>& eventId,
        const TimeValue& newDate,
        ExpandMode mode)
    :SerializableMoveEvent{},
     m_moveEventImplementation(SingletonMoveEventList::instance().get(MoveEventFactoryInterface::Strategy::MOVING)->make(std::move(scenarioPath), eventId, newDate, mode))
{
}

void MoveEventMeta::undo() const
{
    m_moveEventImplementation->undo();
}

void MoveEventMeta::redo() const
{

    m_moveEventImplementation->redo();
}

const Path<ScenarioModel>&MoveEventMeta::path() const
{
    return m_moveEventImplementation->path();
}

void MoveEventMeta::serializeImpl(QDataStream& qDataStream) const
{
    qDataStream << m_moveEventImplementation->serialize();
}

void MoveEventMeta::deserializeImpl(QDataStream& qDataStream)
{
    QByteArray cmdData;

    qDataStream >> cmdData;

    m_moveEventImplementation = SingletonMoveEventList::instance().get(MoveEventFactoryInterface::Strategy::MOVING)->make();

    m_moveEventImplementation->deserialize(cmdData);
}

void MoveEventMeta::update(const Path<ScenarioModel>& scenarioPath,
                           const Id<EventModel>& eventId,
                           const TimeValue& newDate,
                           ExpandMode mode)
{
    m_moveEventImplementation->update(scenarioPath, eventId, newDate, mode);
}

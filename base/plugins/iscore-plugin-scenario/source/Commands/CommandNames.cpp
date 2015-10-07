#include "SetProcessDuration.hpp"
#include "Constraint/SetLooping.hpp"
#include "Constraint/AddRackToConstraint.hpp"
#include "Constraint/AddProcessToConstraint.hpp"
#include "Constraint/AddLayerInNewSlot.hpp"
#include "Constraint/Rack/AddSlotToRack.hpp"
#include "Constraint/Rack/CopySlot.hpp"
#include "Constraint/Rack/Slot/AddLayerModelToSlot.hpp"
#include "Constraint/Rack/Slot/CopyLayerModel.hpp"
#include "Constraint/Rack/Slot/MoveLayerModel.hpp"
#include "Constraint/Rack/Slot/RemoveLayerModelFromSlot.hpp"
#include "Constraint/Rack/Slot/ResizeSlotVertically.hpp"
#include "Constraint/Rack/MergeSlots.hpp"
#include "Constraint/Rack/MoveSlot.hpp"
#include "Constraint/Rack/SwapSlots.hpp"
#include "Constraint/Rack/RemoveSlotFromRack.hpp"
#include "Constraint/ReplaceConstraintContent.hpp"
#include "Constraint/DuplicateRack.hpp"
#include "Constraint/MergeRackes.hpp"
#include "Constraint/RemoveRackFromConstraint.hpp"
#include "Constraint/RemoveProcessFromConstraint.hpp"
#include "Constraint/SetMaxDuration.hpp"
#include "Constraint/SetMinDuration.hpp"
#include "Constraint/SetRigidity.hpp"
#include "Event/SetCondition.hpp"
#include "Event/State/AddStateWithData.hpp"
#include "ClearSelection.hpp"
#include "ResizeBaseConstraint.hpp"

#include "Scenario/Creations/CreateStateMacro.hpp"
#include "Scenario/Creations/CreateState.hpp"
#include "Scenario/Creations/CreateEvent_State.hpp"
#include "Scenario/Creations/CreateTimeNode_Event_State.hpp"
#include "Scenario/Creations/CreateConstraint.hpp"
#include "Scenario/Creations/CreateConstraint_State.hpp"
#include "Scenario/Creations/CreateConstraint_State_Event.hpp"
#include "Scenario/Creations/CreateConstraint_State_Event_TimeNode.hpp"

#include "Scenario/Creations/CreationMetaCommand.hpp"
#include "Scenario/Deletions/ClearConstraint.hpp"
#include "Scenario/Deletions/ClearEvent.hpp"
#include "Scenario/Deletions/RemoveSelection.hpp"
#include "Scenario/Displacement/MoveConstraint.hpp"
#include "Scenario/Displacement/MoveNewEvent.hpp"
#include "Scenario/Displacement/MoveEventMeta.hpp"
#include "Scenario/Displacement/MoveEventOnCreationMeta.hpp"
#include "Scenario/Displacement/MoveNewState.hpp"
#include "Scenario/HideRackInViewModel.hpp"
#include "Scenario/ShowRackInViewModel.hpp"
#include "SwitchStatePosition.hpp"
#include "TimeNode/AddTrigger.hpp"
#include "TimeNode/MergeTimeNodes.hpp"
#include "TimeNode/RemoveTrigger.hpp"
#include "TimeNode/SetTrigger.hpp"
#include "TimeNode/SplitTimeNode.hpp"
#include "Scenario/Displacement/MoveNewEvent.hpp"
#include "Scenario/Displacement/MoveNewState.hpp"


#include <boost/mpl/list/list50.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/preprocessor/iterate.hpp>
#include <boost/config.hpp>

namespace boost { namespace mpl {
#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(51, 100, <boost/mpl/list/aux_/numbered.hpp>))
#include BOOST_PP_ITERATE()
}}
#include <iscore/command/CommandGeneratorMap.hpp>
#include "Control/ScenarioControl.hpp"

#include <Document/Constraint/ConstraintModel.hpp>
#include <Document/Event/EventModel.hpp>
#include <Document/TimeNode/TimeNodeModel.hpp>
#include "Metadata/ChangeElementColor.hpp"
#include "Metadata/ChangeElementComments.hpp"
#include "Metadata/ChangeElementLabel.hpp"
#include "Metadata/ChangeElementName.hpp"

#include <Commands/State/RemoveMessageNodes.hpp>
#include <Commands/State/UpdateState.hpp>

#include <iscore/command/CommandGeneratorMap.hpp>

namespace {
struct ScenarioCommandFactory
{
        static CommandGeneratorMap map;
};
// Instantiation is in CommandNames.cpp

CommandGeneratorMap ScenarioCommandFactory::map;
}
void ScenarioControl::setupCommands()
{
    using namespace Scenario::Command;
    boost::mpl::for_each<
            boost::mpl::list67<

            AddRackToConstraint,
            AddSlotToRack,
            AddProcessToConstraint,
            AddLayerInNewSlot,
            AddLayerModelToSlot,
            UpdateState,
            RemoveMessageNodes,
            UpdateState,
            AddStateWithData,
            AddTrigger,

            ChangeElementColor<ConstraintModel>,
            ChangeElementColor<EventModel>,
            ChangeElementColor<TimeNodeModel>,
            ChangeElementComments<ConstraintModel>,
            ChangeElementComments<EventModel>,
            ChangeElementComments<TimeNodeModel>,
            ChangeElementLabel<ConstraintModel>,
            ChangeElementLabel<EventModel>,
            ChangeElementLabel<TimeNodeModel>,
            ChangeElementName<ConstraintModel>,
            ChangeElementName<EventModel>,
            ChangeElementName<TimeNodeModel>,

            ClearConstraint,
            ClearState,

            DuplicateRack,
            ReplaceConstraintContent,
            CopySlot,

            CreateStateMacro,
            CreateState,
            CreateEvent_State,
            CreateTimeNode_Event_State,
            CreateConstraint,
            CreateConstraint_State,
            CreateConstraint_State_Event,
            CreateConstraint_State_Event_TimeNode,
            CreateSequence,
            CreationMetaCommand,

            ShowRackInViewModel,
            HideRackInViewModel,

            MergeRackes,
            MergeTimeNodes,

            MoveConstraint,
            MoveSlot,
            SwapSlots,
            MoveEventMeta,
            MoveEventOnCreationMeta,
            MoveNewEvent,
            MoveNewState,

            RemoveRackFromConstraint,
            RemoveSlotFromRack,
            ClearSelection,
            RemoveSelection,
            RemoveProcessFromConstraint,
            RemoveLayerModelFromSlot,
            //RemoveStateFromStateModel,

            SetLooping,
            SetProcessDuration,

            MoveBaseEvent,
            ResizeSlotVertically,

            SetCondition,
            SetTrigger,

            SetMaxDuration,
            SetMinDuration,
            SetRigidity,
            SetTrigger,
            RemoveTrigger,

            SplitTimeNode,
            SwitchStatePosition
            >,
            boost::type<boost::mpl::_>
    >(CommandGeneratorMapInserter<ScenarioCommandFactory>());
}



iscore::SerializableCommand *ScenarioControl::instantiateUndoCommand(
        const QString& name,
        const QByteArray& data)
{
    return PluginControlInterface::instantiateUndoCommand<ScenarioCommandFactory>(name, data);
}

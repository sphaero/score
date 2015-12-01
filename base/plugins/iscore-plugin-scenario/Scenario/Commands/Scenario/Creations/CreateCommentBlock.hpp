#pragma once

#include <Scenario/Commands/ScenarioCommandFactory.hpp>

#include <boost/optional/optional.hpp>
#include <iscore/command/SerializableCommand.hpp>

#include <iscore/tools/ModelPath.hpp>
#include <iscore/tools/SettableIdentifier.hpp>

#include <Process/TimeValue.hpp>

class CommentBlockModel;

namespace Scenario
{
    namespace Command
    {
        class CreateCommentBlock final : public iscore::SerializableCommand
        {
                ISCORE_COMMAND_DECL(ScenarioCommandFactoryName(), CreateCommentBlock, "Create a comment block")
            public:
                CreateCommentBlock(
                        const Path<ScenarioModel>& scenarioPath,
                        const TimeValue& date,
                        double yPosition);

                void undo() const override;
                void redo() const override;

            protected:
                void serializeImpl(DataStreamInput&) const override;
                void deserializeImpl(DataStreamOutput&) override;

            private:
                Path<ScenarioModel> m_path;
                TimeValue m_date;
                double m_y;

                Id<CommentBlockModel> m_id;
        };

    }
}

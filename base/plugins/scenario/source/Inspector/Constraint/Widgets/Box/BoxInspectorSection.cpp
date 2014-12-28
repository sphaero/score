#include "BoxInspectorSection.hpp"

#include "AddDeckWidget.hpp"
#include "Deck/DeckInspectorSection.hpp"

#include "Inspector/Constraint/ConstraintInspectorWidget.hpp"

#include "Document/Constraint/ConstraintModel.hpp"
#include "Document/Constraint/Box/BoxModel.hpp"
#include "Document/Constraint/Box/Deck/DeckModel.hpp"

#include "Commands/Constraint/Box/AddDeckToBox.hpp"

#include <QtWidgets/QVBoxLayout>

using namespace Scenario::Command;

BoxInspectorSection::BoxInspectorSection(QString name,
										 BoxModel* box,
										 ConstraintInspectorWidget* parentConstraint):
	InspectorSectionWidget{name, parentConstraint},
	m_model{box}
{
	m_deckSection = new InspectorSectionWidget{"Decks", this};  // TODO Make a custom widget.
	m_deckSection->setObjectName("Decks");

	connect(box,	&BoxModel::deckCreated,
			this,	&BoxInspectorSection::on_deckCreated);

	connect(box,	&BoxModel::deckRemoved,
			this,	&BoxInspectorSection::on_deckRemoved);

	for(auto& deck : m_model->decks())
	{
		addDeckInspectorSection(deck);
	}

	m_deckWidget = new AddDeckWidget{this};
	addContent(m_deckSection);
	addContent(m_deckWidget);
}

void BoxInspectorSection::createDeck()
{
	auto cmd = new AddDeckToBox(
						ObjectPath::pathFromObject(
							"BaseConstraintModel",
							m_model));
	emit submitCommand(cmd);
}

void BoxInspectorSection::addDeckInspectorSection(DeckModel* deck)
{
	DeckInspectorSection* newDeck = new DeckInspectorSection{QString{"Deck.%1"}.arg((SettableIdentifier::identifier_type)deck->id()),
															 deck,
															 this};

	connect(newDeck, &DeckInspectorSection::submitCommand,
			this,	 &BoxInspectorSection::submitCommand);
	m_deckSection->addContent(newDeck);

	m_decksSectionWidgets[(SettableIdentifier::identifier_type)deck->id()] = newDeck;
}


void BoxInspectorSection::on_deckCreated(int deckId)
{
	// TODO display them in the order of their position.
	// TODO issue : the box should grow of 10 more pixels for each deck.
	addDeckInspectorSection(m_model->deck(deckId));
}

void BoxInspectorSection::on_deckRemoved(int deckId)
{
	auto ptr = m_decksSectionWidgets[deckId];
	m_decksSectionWidgets.remove(deckId);

	if(ptr)
	{
		ptr->deleteLater();
	}
}

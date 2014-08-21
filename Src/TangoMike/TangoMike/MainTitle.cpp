#include "stdafx.h"
#include "MainTitle.h"


MainTitle::MainTitle()
	:word1_(), word2_(), word3_()
{
	LoadTextFromXml();
	AddChild(&word1_);
	AddChild(&word2_);
	AddChild(&word3_);
}


MainTitle::~MainTitle()
{
}


void MainTitle::Update(float dTime)
{
	Component::Update(dTime);
}

void MainTitle::Render()
{
	Component::Render();
}

void MainTitle::LoadTextFromXml()
{
	pugi::xml_document doc;
	auto result = doc.load_file(XML_FILE_NAME);
	

	if (result)
	{
		std::cout << "Success description: " << result.description() << "\n";

		auto xmlMainTitle = doc.child(L"ShowItems").child(L"MainTitle");

		auto xmlWord1 = xmlMainTitle.child(L"Word1");
		word1_.SetContents(xmlWord1.attribute(L"Contents").value());
		word1_.SetPosition(
			D2D1::Point2F(xmlWord1.attribute(L"Left").as_int(), xmlWord1.attribute(L"Top").as_int()));
		word1_.SetFontSize(xmlWord1.attribute(L"FontSize").as_float());

		auto xmlWord2 = xmlMainTitle.child(L"Word2");
		word2_.SetContents(xmlWord2.attribute(L"Contents").value());
		word2_.SetPosition(
			D2D1::Point2F(xmlWord2.attribute(L"Left").as_int(), xmlWord2.attribute(L"Top").as_int()));
		word2_.SetFontSize(xmlWord2.attribute(L"FontSize").as_float());

		auto xmlWord3 = xmlMainTitle.child(L"Word3");
		word3_.SetContents(xmlWord3.attribute(L"Contents").value());
		word3_.SetPosition(
			D2D1::Point2F(xmlWord3.attribute(L"Left").as_int(), xmlWord3.attribute(L"Top").as_int()));
		word3_.SetFontSize(xmlWord3.attribute(L"FontSize").as_float());

	}
	else
	{
		std::cout << "Error description: " << result.description() << "\n";
		std::cout << "Error offset: " << result.offset << " (error at [..." << (XML_FILE_NAME + result.offset) << "]\n\n";
		Assert("error load xml");
	}

}

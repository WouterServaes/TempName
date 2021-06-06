#pragma once
#include "Minigin.h"
class QBertGame final: public Minigin
{
public:
	QBertGame() = default;
	~QBertGame() override = default;
	QBertGame(const QBertGame& other) = delete;
	QBertGame(QBertGame&& other) noexcept = delete;
	QBertGame& operator=(const QBertGame& other) = delete;
	QBertGame& operator=(QBertGame&& other) noexcept = delete;

protected:
	void LoadGame() override;
};

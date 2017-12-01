#include "Game2AU.h"

void Game2AU::Unmarshal()
{
    this->operator >>(userid);
    this->operator >>(qtype);
    this->operator >>(info);
    this->operator >>(reserved);
    Utils::print(QString("Game2AU userid: %1, qtype: %2, info: %3, reserved: %4")
                 .arg(userid).arg(qtype).arg("").arg(reserved));
}

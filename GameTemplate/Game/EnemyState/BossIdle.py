from Game import ChangeState
from Game import GetLengthToPlayer
from Game import Move
from Game import Rotate
from Game import AnimationUpdate
from Game import UpdateTriggerBox
from Game import JudgeDamage
from Game import NoticePlayer

def Update() :

    #移動関数呼び出し。
    Move()

    #回転関数呼び出し。
    Rotate()

    #ダメージ判定
    JudgeDamage()

    #プレイヤーとの距離を調べる。
    lengthToPlayer = GetLengthToPlayer()

    #プレイヤーとの距離が500以下ならプレイヤーに近づく。
    if(NoticePlayer()):
        ChangeState(1)

    #アニメーションを更新。
    AnimationUpdate()

    #トリガーボックスを更新。
    UpdateTriggerBox()
    
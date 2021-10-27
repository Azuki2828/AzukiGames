from Game import Move
from Game import Rotate
from Game import ChangeState
from Game import GetLengthToPlayer
from Game import SetCoolTime
from Game import AnimationUpdate

def Update():

    #移動関数。
    Move()

    #回転関数。
    Rotate()


    #プレイヤーとの距離を調べる。
    lengthToPlayer = GetLengthToPlayer()


    #プレイヤーとの距離が120以下なら攻撃態勢に入る。
    if(lengthToPlayer <= 120.0):
        ChangeState(2)

        #クールタイムを3.0秒に設定。
        SetCoolTime(3.0)
    #プレイヤーとの距離が500より遠いなら待機状態に。
    elif(lengthToPlayer > 500.0):
        ChangeState(0)

    #アニメーションを更新。
    AnimationUpdate()

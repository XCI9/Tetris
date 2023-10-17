# Tetris
Classics tetris coded with Qt. Allow players to play double on remote. 

# Rule introduction
There are many standard in Tetris. The most rule I use is same as Tetris99. Basic rules follow the [tetris guideline](https://tetris.fandom.com/wiki/Tetris_Guideline). Details are list below:

- Rotation: The rotation rule I use is SRS(Super Rotation System). Which will try five places to place the tetrominoes after rotation. The rotation lookup table can find [here](https://tetris.fandom.com/wiki/SRS)
- Scoring and Garbage: The score and the garbage line to send is following the below table:

| Action            | Score    | Garbage Line |
|-------------------|----------|--------------|
| Single Line       | 100      | 0            |
| Double Line       | 300      | 1            |
| Triple Line       | 500      | 2            |
| Tetris            | 800      | 4 (+2)       |
| Tspin Mini Single | 200      | 0 (+1)       |
| Tspin Mini Double | 400      | 1 (+1)       |
| Tspin Single      | 800      | 1 (+1)       |
| Tspin Double      | 1200     | 2 (+2)       |
| Tspin Triple      | 1600     | 6 (+3)       |
| All Clear         | +0       | +10          |
| 1-2 combo         | +0       | +1           |
| 3-4 combo         | +0       | +2           |
| 5-6 combo         | +0       | +3           |
| 7-9 combo         | +0       | +4           |
| more than 9 combo | +0       | +5           |
| Hard Drop         | +2/block | -            |

ps. number in () is the back to back bonus

- Lock system: Tetraminoes will be locked after 36 frames of touching the ground.
  After touching the grounds and before locking, if player perform a valid operation, the lock timer will be reset, it can be reset up to 15 times.
- Summon system: seven different tetraminoes are called "a bag".
  Each time the number of tetraminoes in queue is less than 8, the summon system will put a new bag into the queue.
  Note that the order in a bag in random.

# Setting
- In the setting, you can change the binding key of every operation.

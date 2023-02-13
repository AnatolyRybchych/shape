
import math
import struct

def lerp(from_:float, to:float, progress:float) -> float:
    return from_ + (to - from_) * progress

def circle(file:str, cx:float, cy:float, cr:float) -> None:
    w:int = 128
    h:int = 128

    with open(file, 'wb') as f:
        f.write(bytes("SHAPE \n\0", "ascii"))
        f.write(int(w).to_bytes(4, 'little'))
        f.write(int(h).to_bytes(4, 'little'))

        for y in range(h):
            for x in range(w):
                rel_x:float = x / w * 2.0 - 1.0
                rel_y:float = y / h * 2.0 - 1.0

                f.write(struct.pack('<f', cr - math.dist([rel_x, rel_y], [cx, cy])))

circle('circle1.shape', 0, 0, 0.1)
circle('circle2.shape', 0, 0.5, 0.5)

# Notes

## Result

![](result.gif)

## Scaling

$\left[\begin{matrix}S_1 & 0 & 0 & 0 \\ 0 & S_2 & 0 & 0 \\ 0 & 0 & S_3 & 0 \\ 0 & 0 &0 & 1 \end{matrix}\right] \cdot{\left(\begin{matrix}x \\ y \\ z \\ 1 \end{matrix}\right)}=\left(\begin{matrix}S_1\cdot x \\ S_2\cdot y \\ S_3\cdot z \\ 1 \end{matrix}\right)$

## Translation

$\left[\begin{matrix} 1 & 0 & 0 & T_x \\ 0 & 1 & 0 & T_y \\ 0 & 0 & 1 & T_z \\ 0 & 0 &0 & 1 \end{matrix}\right] \cdot{\left(\begin{matrix}x \\ y \\ z \\ 1 \end{matrix}\right)}=\left(\begin{matrix}x+T_x \\ y+T_y \\ z+T_z \\ 1 \end{matrix}\right)$

## Rotation

$\left[\begin{matrix} \cos \theta + R_x^2(1-\cos \theta) & R_xR_y(1-\cos \theta)-R_z\sin \theta & R_xR_z(1-\cos \theta)+R_y\sin \theta & 0 \\ R_yR_x(1-\cos\theta)+R_z\sin\theta & \cos\theta + R_y^2(1-\cos\theta) & R_yR_z(1-\cos\theta)-R_x\sin\theta & 0 \\ R_zR_x(1-\cos\theta)-R_y\sin\theta & R_zR_y(1-\cos\theta)+R_x\sin\theta & \cos\theta + R_z^2(1-\cos\theta) & 0 \\ 0 & 0 &0 & 1 \end{matrix}\right]$

### Gimbal Lock
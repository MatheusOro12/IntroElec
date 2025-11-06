import cv2
import os
import natsort

#endereço das imagens
folder = "fotos"


images = [img for img in os.listdir(folder) if img.lower().endswith((".jpg", ".jpeg", ".png"))]
images = natsort.natsorted(images)

if len(images) == 0:
    raise Exception("Nenhuma imagem encontrada na pasta!")

# Carrega a primeira imagem para pegar o tamanho
first_frame = cv2.imread(os.path.join(folder, images[0]))
height, width, _ = first_frame.shape

out = cv2.VideoWriter("timelapse.mp4", cv2.VideoWriter_fourcc(*"mp4v"), 30, (width, height))

print("Gerando vídeo...")

for img_name in images:
    img_path = os.path.join(folder, img_name)
    frame = cv2.imread(img_path)
    out.write(frame)

out.release()
print("Timelapse finalizado! Arquivo salvo como: timelapse.mp4")


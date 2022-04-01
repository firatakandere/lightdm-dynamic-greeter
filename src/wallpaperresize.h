#ifndef IMAGESCALE_H
#define IMAGESCALE_H

#include <QImage>
#include <QPainter>
#include <QObject>

namespace WallpaperResize {


	Q_ENUM(Mode);

	QImage make_scaled(const QImage &image, const int win_w, const int win_h)
	{
		return image.scaled(win_w, win_h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	}

	QImage make_center(const QImage &image, const int win_w, const int win_h)
	{
		int dest_x = (win_w - image.width()) >> 1;
		int dest_y = (win_h - image.height()) >> 1;
		int src_x = 0;
		int src_y = 0;
		int cpy_w = image.width();
		int cpy_h = image.height();

		if (image.width() > win_w)
		{
			src_x = (image.width() - win_w) >> 1;
			dest_x = 0;
			cpy_w = win_w;
		}

		if (image.height() > win_h)
		{
			src_y = (image.height() - win_h) >> 1;
			dest_y = 0;
			cpy_h = win_h;
		}

		QImage outputImage(win_w, win_h, image.format());
		QPainter painter(&outputImage);
		painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
		painter.drawImage(dest_x, dest_y, image, src_x, src_y, cpy_w, cpy_h);
		return outputImage;
	}

	QImage make_zoom(const QImage &image, const int win_w, const int win_h)
	{
		int x, y, res_x, res_y;

		int img_h = image.height();
		int img_w = image.width();

		if (img_w > img_h && ((float)img_w / (float)img_h) > ((float)win_w / (float)win_h))
		{
			res_x = win_w;
			res_y = (int)(((float)(img_h * res_x)) / (float)win_w);
			x = 0;
			y = (win_h - res_y) >> 1;
		}
		else
		{
			res_y = win_h;
			res_x = (int)(((float)(img_w * res_y)) / (float)img_h);
			y = 0;
			x = (win_w - res_x) >> 1;
		}

		if (res_x > win_w)
			res_x = win_w;
		if (res_y > win_h)
			res_y = win_h;
		if (x < 0)
			x = 0;
		if (y < 0)
			y = 0;

		QImage tmpScaledImage = image.scaled(res_x, res_y, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

		QImage outputImage(win_w, win_h, image.format());
		QPainter painter(&outputImage);
		painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
		painter.drawImage(x, y, tmpScaledImage, 0, 0, tmpScaledImage.width(), tmpScaledImage.height());
		return outputImage;
	}

	QImage make_zoom_fill(const QImage *image, const int win_w, const int win_h)
	{
		int x, y, w, h;

		int img_w = image->width();
		int img_h = image->height();

		x = 0;
		w = win_w;
		h = win_w * (img_h / img_w);
		y = (h - win_h) / 2;

		if (h < win_h)
		{
			y = 0;
			w = win_h * (img_w / img_h);
			h = win_h;
			x = (x - win_w) / 2;
		}

		QImage tmpScaledImage = image->scaled(w, h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

		QImage outputImage(win_w, win_h, image->format());
		QPainter painter(&outputImage);
		painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
		painter.drawImage(0, 0, tmpScaledImage, x, y, win_w, win_h);
		return outputImage;
	}

}

#endif // IMAGESCALE_H

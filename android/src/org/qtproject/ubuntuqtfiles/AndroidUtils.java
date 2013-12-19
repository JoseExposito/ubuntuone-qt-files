/*
 * This file is part of UbuntuOne Qt Files.
 *
 * UbuntuOne Qt Files is free software:  you can redistribute it  and/or  modify it under the terms of the  GNU  General
 * Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 *
 * UbuntuOne Qt Files  is distributed in the hope  that it will be useful,  but  WITHOUT ANY WARRANTY;  without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with Foobar.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
package org.qtproject.ubuntuqtfiles;

import java.io.File;
import android.content.Intent;
import android.net.Uri;
import android.os.Environment;
import android.webkit.MimeTypeMap;
import android.annotation.SuppressLint;
import android.app.DownloadManager;
import android.content.Context;
import android.database.Cursor;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;

public class AndroidUtils extends org.qtproject.qt5.android.bindings.QtActivity {

    private static AndroidUtils instance;

    public AndroidUtils() {
        this.instance = this;
    }

    public static void openFile(String filePath) {
        File   file = new File(filePath);
        String extension = "";
        int i = filePath.lastIndexOf('.');
        int p = Math.max(filePath.lastIndexOf('/'), filePath.lastIndexOf('\\'));
        if (i > p)
            extension = filePath.substring(i+1);
        String type = MimeTypeMap.getSingleton().getMimeTypeFromExtension(extension.toLowerCase());

        if (type == null)
            type = "*/*";

        Intent intent = new Intent(Intent.ACTION_VIEW);
        intent.setDataAndType(Uri.fromFile(file), type);
        instance.startActivity(intent);
    }

    public static void getSDCardPath(String retValue) {
        retValue = Environment.getExternalStorageDirectory().getAbsolutePath();
    }

    public static void shareLink(String link) {
        Intent share = new Intent(Intent.ACTION_SEND);
        share.setType("text/plain");
        share.putExtra(Intent.EXTRA_TEXT, link);
        instance.startActivity(Intent.createChooser(share, ""));
    }

    @SuppressWarnings("deprecation")
    @SuppressLint("NewApi")
    public static void downloadFile(String url, String localSaveDir, String localSaveName) {
        DownloadManager.Request request = new DownloadManager.Request(Uri.parse(url));
        request.setDestinationInExternalPublicDir(localSaveDir, localSaveName);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB) {
            request.setNotificationVisibility(DownloadManager.Request.VISIBILITY_VISIBLE);
        } else {
            request.setShowRunningNotification(true);
        }

        final DownloadManager manager = (DownloadManager)instance.getSystemService(Context.DOWNLOAD_SERVICE);
        final long downloadId = manager.enqueue(request);

        new Thread(new Runnable() {

            @Override
            public void run() {
                boolean downloading = true;
                while (downloading) {
                    Cursor cursor = manager.query(new DownloadManager.Query().setFilterById(downloadId));
                    cursor.moveToFirst();

                    // TODO Add progress signal
                    int bytes_downloaded = cursor.getInt(cursor.getColumnIndex(DownloadManager.COLUMN_BYTES_DOWNLOADED_SO_FAR));
                    int bytes_total = cursor.getInt(cursor.getColumnIndex(DownloadManager.COLUMN_TOTAL_SIZE_BYTES));
                    int progress = (int) ((bytes_downloaded * 100l) / bytes_total);

                    int status = cursor.getInt(cursor.getColumnIndex(DownloadManager.COLUMN_STATUS));
                    if (status == DownloadManager.STATUS_SUCCESSFUL) {
                        // TODO Add finish signal
                        downloading = false;

                    } else if (status == DownloadManager.STATUS_FAILED) {
                        // TODO Add error signal
                        downloading = false;
                    }

                    cursor.close();
                }
            }
        }).start();
    }
}

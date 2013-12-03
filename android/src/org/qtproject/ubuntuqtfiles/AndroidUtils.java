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

public class AndroidUtils extends org.qtproject.qt5.android.bindings.QtActivity {

    private static AndroidUtils instance;

    public AndroidUtils() {
        this.instance = this;
    }

    public static void openFile(String filePath) {
        File file   = new File(filePath);
        String ext  = MimeTypeMap.getFileExtensionFromUrl(file.toURI().toString());
        String type = MimeTypeMap.getSingleton().getMimeTypeFromExtension(ext);

        if (type == null)
            type = "*/*";

        Intent intent = new Intent(Intent.ACTION_VIEW);
        intent.setDataAndType(Uri.fromFile(file), type);
        instance.startActivity(intent);
    }

    public static void getSDCardPath(String retValue) {
        retValue = Environment.getExternalStorageDirectory().getAbsolutePath();
    }
}

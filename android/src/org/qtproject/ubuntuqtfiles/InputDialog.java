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

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.widget.EditText;

public class InputDialog {

    private static native void showInputDialogResultCallback(String result);
    public static void showInputDialog(final AndroidUtils instance, final String title, final String description,
            final String defaultInput, final String okButtonTitle, final String cancelButtonTitle) {
        instance.runOnUiThread(new Runnable() { public void run() {
            final EditText input = new EditText(instance);
            input.setText(defaultInput);
            input.setSingleLine();
            new AlertDialog.Builder(instance)
                .setTitle(title)
                .setMessage(description)
                .setView(input)
                .setCancelable(false)
                .setPositiveButton(okButtonTitle, new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int whichButton) {
                        showInputDialogResultCallback(input.getText().toString());
                    }
                }).setNegativeButton(cancelButtonTitle, new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int whichButton) {
                        showInputDialogResultCallback("");
                    }
                }).show();
        }});
    }
}

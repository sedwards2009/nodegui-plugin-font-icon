import { QFont, QIcon } from '@nodegui/nodegui';

import addon from './addon';

/**
 *
 *
 */
export function createIcon(font: QFont, text: string): QIcon {
    const qiconNative = addon.FontIconCreateIcon(font.native, text);
    return new QIcon(qiconNative);
}

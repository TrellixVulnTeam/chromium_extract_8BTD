# Copyright (c) 2011 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
{
  'targets': [
    {
      'target_name': 'chromium_extract',
      'type': 'none',
      'dependencies': [
        #׮ʵ�ֿ⣨goolge gmock��
        '../testing/gmock.gyp:gmock',
        #��Ԫ���Կ⣨google gtest��
        '../testing/gtest.gyp:gtest',
        #�ڴ����
        '../base/allocator/allocator.gyp:allocator',
        #���Ի�����
        '../base/base.gyp:base',
        #���Ի����⣨i18n��
        '../base/base.gyp:base_i18n',
        #�����
        '../net/net.gyp:net',
        #http������ʵ�ֿ�
        '../net/net.gyp:http_server',
        #SQLite��������SQLCipherʵ�֣�
        '../third_party/sqlite/sqlite.gyp:sqlite',
        #SQLite��װ��
        '../sql/sql.gyp:sql',
        #UI������
        '../ui/base/ui_base.gyp:ui_base',
        #UI��ͼ�����
        '../ui/views/views.gyp:views',
        #UI��ͼ���ʾ��
        '../ui/views/examples/examples.gyp:views_examples_exe',
        #UIƤ���⣨google aura��
        '../ui/aura/aura.gyp:aura',
        '../ui/aura_extra/aura_extra.gyp:aura_extra',
        #UI���ƿ⣨google gfx��
        '../ui/gfx/gfx.gyp:gfx',
        #UI��Դ��
        '../ui/app_list/resources/app_list_resources.gyp:app_list_resources',
        #���ܿ⹤�ߣ�����third_party/boringssl��һ��OpenSSL���֣��������ٶȣ�
        '../crypto/crypto.gyp:crypto',
        #boringssl�⣨openssl�����
        '../third_party/boringssl/boringssl.gyp:boringssl',
        #��ӡ��
        '../printing/printing.gyp:printing',
        #���󱨸��ת������⣨google breakpad��
        '../breakpad/breakpad.gyp:breakpad_handler',
        #���󱨸��ϴ��⣨google breakpad��
        '../breakpad/breakpad.gyp:breakpad_sender',
      ],
    },
  ],
}

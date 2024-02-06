from argostranslate import package, translate

package.install_from_path('translate-es_en-1_0.argosmodel')

installed_languages = translate.get_installed_languages()
print([str(lang) for lang in installed_languages])
translation_en_es = installed_languages[1].get_translation(installed_languages[0])
print(translation_en_es.translate("If I had gone to Paris last year, I wouldn't have money now."))
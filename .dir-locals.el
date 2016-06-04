((c++-mode . ( ;; Make includes work properly
              (eval .
                    (set (make-local-variable
                          'flycheck-gcc-include-path)
                         (set (make-local-variable
                               'flycheck-clang-include-path)
                              (let ((dir-locals-dir
                                     (let ((d (directory-file-name
                                               (file-name-directory
                                                buffer-file-name))))
                                       (while (not (file-exists-p
                                                    (format "%s/%s" d
                                                            ".dir-locals.el")))
                                         (setq d (directory-file-name
                                                  (file-name-directory
                                                   d))))
                                       d)))
                                (list (format "%s/%s" dir-locals-dir
                                              "src")
                                      (format "%s/%s" dir-locals-dir
                                              "catch-raw")
                                      (format "%s/%s" dir-locals-dir
                                              "plugins"))))))
              (eval .
                    (set (make-local-variable 'flycheck-gcc-warnings)
                         (set (make-local-variable
                               'flycheck-clang-warnings)
                              (list "everything" "no-c++98-compat"
                                    "no-c++98-compat-pedantic"
                                    "no-exit-time-destructors"
                                    "no-global-constructors"
                                    "no-documentation-unknown-command"
                                    "no-shadow" "no-padded"
                                    "no-weak-vtables"))))))
 ;; apply to all source directories (including plugins)
 (subdirs . t))
